## libtf2mod

### What this is
This project implements a bare-bones framework for making low-level Team Fortress 2 dedicated server mods, using live code patching and function hooking techniques.

It also includes various built-in mods authored by me, which are intended to fix or enhance various aspects of TF2's Mann vs Machine mode.

I started this project so I could automate the process of creating TF2 MvM mods. SourceMod was too restricting, and C++'s type system was too annoying, so I wrote my own mod framework in C.

### Compatibility
This project will only work with the Linux TF2 dedicated server (srcds).

The Windows version of srcds doesn't have function symbols. And the initial hooking method would have to be different.

### How to compile
Use the Makefile. You should probably already know how to do this.

### How to install
When running the game via `srcds_run`, set the environment variable `LD_PRELOAD` to the full path of `libtf2mod.so`. This will force the game binary `srcds_linux` to load the mod library whether it wants to or not.

### Will this get me VAC banned?
If used as intended with the TF2 dedicated server, no.

If for some reason you decided to modify this project to patch/hook the TF2 game client instead, then yes, it could get you VAC banned.

### How this works
We override the `dlopen` function (provided by libdl) with our own wrapper so that we can intercept the loading of `server_srv.so` (the library containing the server-side game code).

When the server binary is loaded, we load its ELF symbol table to figure out where the functions are (annoyingly, all of the functions are in the symbol table, but are marked as private, so we can't directly link against them). Then we apply our patches and detours to various functions in the server binary. After that, we stop interfering with the program's execution and allow it to continue normally.

Patches run a CHECK routine, which verifies that the instructions the patch expects to be at a particular function offset are actually still there. If the CHECK routine doesn't run into any problems, then the APPLY routine is run, which actually modifies the instructions. This system should generally prevent patches from running if the game code is changed; instead of running amok, the affected patch(es) will be disabled until someone can come along and manually update them to be compatible.

Detours (hooks) are more reliable than patches, because they intercept function parameters and/or modify function return values instead of modifying individual instructions. However, it's not always feasible to make certain modifications without patching the game code. The detour system in this project overwrites the first few instructions of the target function and then jumps to a trampoline buffer containing those instructions to resume execution. This means it's possible to hook non-virtual functions.
