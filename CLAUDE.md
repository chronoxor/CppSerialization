# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project purpose

CppSerialization is a comparison harness as much as it is a library. It wraps seven serialization backends — Cap'n'Proto, FastBinaryEncoding (FBE), FlatBuffers, Protobuf, SimpleBinaryEncoding (SBE), zpp::bits, and JSON (RapidJSON) — around a single shared domain model so they can be benchmarked head-to-head.

The only "library" code in `include/serialization/` and `source/serialization/` is the JSON helper (Serializer / Deserializer / Parser thin wrappers over RapidJSON). All other protocols live entirely in their upstream libraries plus generated code under `proto/`. The cppserialization library target is therefore lean — the heavy lifting is in the per-protocol `examples/`, `performance/`, and `tests/` files.

## Bootstrapping the repo

Submodules are managed by [gil](https://github.com/chronoxor/gil), **not** git submodules. After cloning, you must run:

```shell
pip3 install gil
gil update
```

This populates `modules/` (capnproto, Catch2, CppBenchmark, CppCommon, flatbuffers, protobuf, rapidjson, zpp_bits) and the auxiliary `build/` and `cmake/` directories (which are themselves separate git repos: CppBuildScripts and CppCMakeScripts). Without `gil update`, CMake configuration will fail. The `build/` directory is *not* a CMake build dir — it holds platform launcher scripts.

Linux also needs system packages: `sudo apt-get install -y binutils-dev uuid-dev`.

## Building, testing, running

All builds go through wrapper scripts in `build/` that invoke CMake out-of-source:

```shell
cd build
./unix.sh        # Linux, macOS, Cygwin, MSYS2
./mingw.bat      # Windows MinGW
./vs.bat         # Windows Visual Studio
```

Direct CMake also works (`cmake -B <dir> && cmake --build <dir>`). Output binaries are installed to `bin/`.

Run tests:

```shell
ctest --test-dir <build-dir>                    # via CTest
./bin/cppserialization-tests                    # directly, all suites
./bin/cppserialization-tests "[json]"           # single Catch2 tag
./bin/cppserialization-tests --list-tests       # list available tests
```

CTest is wired with `--durations yes --order lex`. Catch2 is the amalgamated single-header from `modules/Catch2/`.

Examples and benchmarks are separate executables, one per protocol, named `cppserialization-example-<proto>` and `cppserialization-performance-<proto>_(serialize|deserialize)`.

Java is required for SBE schema regeneration via the bundled `modules/sbe/sbe-all-1.37.1.jar`; CMake skips it under Cygwin.

## Code generation pipeline

`CMakeLists.txt` runs four code generators at configure/build time over the schema files in `proto/`:

| Schema                   | Tool                          | Output                          |
| ------------------------ | ----------------------------- | ------------------------------- |
| `proto/trade.capnp`      | `capnp_generate_cpp` (capnpc) | `proto/capnproto/trade.capnp.*` |
| `proto/trade.fbs`        | `flatc --cpp --scoped-enums`  | `proto/flatbuffers/*_generated.h` |
| `proto/trade.proto`      | `protoc --cpp_out`            | `proto/protobuf/trade.pb.*`     |
| `proto/trade.sbe.xml`    | `sbe-all-*.jar` (Java)        | `proto/sbe/*.h`                 |
| `proto/trade.fbe`        | **pre-generated**, checked in | `proto/fbe/*.{h,cpp,inl}`       |

FBE output is committed to the repo because the FBE compiler is not built here. zpp::bits is header-only — no generation step. JSON has no schema. The combined `proto` library target compiles all generated sources and is what every example/test/benchmark links against.

When changing the domain model, update **all of** `proto/trade.h` (the canonical C++ struct + per-protocol Serialize/Deserialize methods), `proto/trade.capnp`, `proto/trade.fbs`, `proto/trade.proto`, `proto/trade.sbe.xml`, and `proto/trade.fbe`. The first four regenerate automatically; FBE generated output must be regenerated externally and re-committed.

## Domain model and the Serialize/Deserialize convention

`proto/trade.h` defines `TradeProto::{Order, Balance, Account}` and is included by every example, benchmark, and test. Each struct exposes seven overload sets — one per backend — by overloading `Serialize` / `Deserialize` on the backend's builder/reader/model type:

- Cap'n'Proto: `(Trade::capnproto::X::Builder&)` and `(const Trade::capnproto::X::Reader&)`
- FBE: `(FBE::FieldModel<trade::X>&)` for both directions
- FlatBuffers: `(flatbuffers::FlatBufferBuilder&) -> Offset<...>` and `(const Trade::flatbuf::X&)`
- Protobuf: `(Trade::protobuf::X&) -> X&` and `(const Trade::protobuf::X&)`
- SBE: `(sbe::X&)` for both directions
- zpp::bits: declares `using serialize = zpp::bits::members<N>;` only — call site does the work
- JSON: templated on `Serializer<OutputStream>` / generic JSON value type

Adding a new field requires updating every overload (and the schemas listed above). Missing one will compile fine for the protocols that don't reference it but silently drop the field for those that do.

## Layout

- `include/serialization/`, `source/serialization/` — the thin JSON wrapper that is the actual cppserialization library.
- `proto/` — schemas (`trade.*`) plus generated/checked-in code per backend, plus the canonical `trade.h` domain model with all serialization overloads.
- `examples/`, `performance/`, `tests/` — one file per backend, all including `proto/trade.h`. Tests use Catch2 with one TEST_CASE per protocol; benchmarks use CppBenchmark.
- `modules/` — gil-managed dependencies. **Do not** edit; they are independent git checkouts.
- `cmake/` — gil-managed CMake helper scripts (CppCMakeScripts repo).
- `build/` — gil-managed launcher scripts (CppBuildScripts repo). Not a build output dir.
- `bin/` — install destination for executables.

## Conventions

- The library is header-mostly; new utilities follow the `*.h` + `*.inl` (template definitions) pattern seen in `include/serialization/json/`.
- File header doxygen comment with `\file`, `\brief`, `\author`, `\date`, `\copyright MIT License` is used throughout — match it for new files.
- The JSON wrapper customizes RapidJSON via `RAPIDJSON_NAMESPACE = CppSerialization::JSON` (set in `json.h`). Don't include RapidJSON headers directly elsewhere — go through `serialization/json/json.h`.
- Compile flags come from `cmake/SetCompilerWarnings.cmake` as `${PEDANTIC_COMPILE_FLAGS}`. The generated `proto` target relaxes these for the third-party generated code.
