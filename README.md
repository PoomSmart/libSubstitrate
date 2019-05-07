# libSubstitrate

That is, (Substi)ute + Cydia Subs(trate). This is a compatibility library for runtime modification tweaks via Substitute and Cydia Substrate.

The motivation of this project is the lack of Substrate support on A12/arm64e for those using Chimera. As Substitute API usually works better on this environment, libSubstitrate will, if available, try to use Substitute API first. Otherwise, it will fall back to Cydia Substrate.

To use this library, include `substitrate.h` in your project.