# NextBasic

NextBasic is an open-source, easy to use programming language which generates 32-bits applications for Windows, Mac (Intel only) and Linux.

The nbc and nbmake tools are released under the terms of the GNU General Public License version 3 (included in the file gplv3.txt).

The language modules are released under the Zlib license (included in the file zlib.txt).

Modules that are simple bindings for other libraries (like SDL2) retain the same license as the original library.

## TODO:
- [ ] Replace QtCreator projects with CMake
- [ ] Replace Struct... EndStruct with Type... EndType
- [ ] Replace Dim and Const with Var and Let
- [ ] Replace Free functions with Delete functions?
- [ ] Replace PChar with CString

- [ ] Add Opaque Type
- [ ] Make pointers in modules use opaque types (function pointers should be of opaque type FuncHandle)
- [ ] Non opaque types should be handled by std::shared_ptr (making Delete unneeded but still reserved)

- [ ] Add "." as operator in parser (do not use ParseVarAccess)
- [ ] Remove support for direct function pointers (add FunctionHandle(name$) As FuncHandle)?
- [ ] Fix type field names clashing with global names
- [ ] Add bitwise operators

- [ ] Builtin arrays (no CreateArray nor FreeArray) as reference types
- [ ] Var arr[x] creates a fixed array on the stack
- [ ] Var arr[] creates a dynamic array
- [ ] Var arr[][] creates multdimensional arrays
- [ ] Arrays as arguments cannot be specified as fixed
- [ ] Add <- insertion operator, with the same precedence as =

- [ ] Rewrite Core module in C
- [ ] Rewrite compiler in NextBasic
- [ ] Use C output instead of C++
- [ ] Remove "Linkage:C" Extern option

- [ ] Add builtin support for maps
- [ ] Add Android and iOS targets
- [ ] Add doc generator
- [ ] Add documentation
- [ ] Add examples
- [ ] Add StaticLib, SharedLib to $Option directive (static and shared lib generation support)
- [ ] Add $If, $ElseIf, $Else, $EndIf, with directives: Windows, Mac, Linux, iOS, Android, Phone, Tablet, Arch32, Arch64
- [ ] Copy shared libraries with executable
- [ ] Add unicode support
- [ ] Add type inference

## Modules TODO:
- [ ] Add dialog module
- [ ] Add Urho3D module
- [ ] Add Lua module
- [ ] Add INI module
- [ ] Add JSON module
- [ ] Add XML module
- [ ] Add SDL, SDL_image, SDL_gfx, SDL_mixer and SDL_net modules (SDL2)
- [ ] Add libui module
- [ ] Add 3D math module
- [ ] Add PicoGfx, Next2D and Next3D modules