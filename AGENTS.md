# AGENTS.md

## Project summary

- This repository is a **Windows MFC SDI desktop app** controlling a **hollow torsional shear triaxial test apparatus** (axial load and torque applied independently to a hollow cylinder specimen).
- Toolchain assumptions are **Visual Studio 2022 + MFC (dynamic)**, toolset `v143`, **MBCS / MultiByte** (`CharacterSet=MultiByte`, *not* Unicode). Win32 and x64 configurations exist; **x64 is the primary target**.
- AD/DA communication is implemented through the **CONTEC AIO-WDM driver (CAIO API)** via `src/caio.lib` / `src/CAIO.H`.
- Derived from DigitShowBasic. Licensed under **GPLv3**.

## Build / test / lint

### Build

From repository root:

```powershell
& "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" "DigitShowBasic.sln" /p:Configuration=Debug /p:Platform=x64 /nologo
```

```powershell
& "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" "DigitShowBasic.sln" /p:Configuration=Release /p:Platform=x64 /nologo
```

### Test

- No automated test project is currently configured in this repository.
- No single-test command exists.

### Lint / static checks

- No dedicated lint command is configured.

### ABSOLUTE RULE — Definition of "edit complete"

A change counts as complete only after a clean build (**0 errors**) with the Release x64 command above, ideally also Debug x64. Do not commit code that does not build. Compare warnings against the existing baseline; do not introduce new ones.

## High-level architecture

### MFC structure

- `src/DigitShowBasic.cpp`: `CWinApp` entrypoint and SDI app initialization.
- `src/MainFrm.cpp`: main window and menu command routing for control dialogs.
- `src/DigitShowBasicView.cpp`: form view UI + timer-driven runtime loop.
- `src/DigitShowBasicDoc.cpp`: hardware I/O, calibration math, control algorithms, torque membrane correction, data saving.
- `src/DigitShowContext.h/.cpp`: **global runtime state singleton** (`GetContext()` / `InitContext()`). All former extern globals live here.
- Dialogs (`Control_*.cpp`, `Specimen.cpp`, `CalibrationFactor.cpp`, `BoardSettings.cpp`, `DA_Channel.cpp`, `DA_Vout.cpp`, `SamplingSettings.cpp`) read shared state from the context on init and write it back in `OnOK` / update handlers after `UpdateData(TRUE)`.

### Global runtime state and hardware singletons

- `DigitShowContext` (`DigitShowContext.h`) is a lazily initialized global singleton via `GetContext()`.
- Each function that needs state starts with `DigitShowContext* ctx = GetContext();`.
- Hardware board handles are stored in `ctx->ad[i].Id` (AI board `"AIO000"`, up to 2 boards) and `ctx->da[0].Id` (AO board `"AIO001"`).
- Do **not** reintroduce file-scope globals or `extern` declarations; add fields to `DigitShowContext` instead.

### Hardware

- AI board(s): device name `"AIO000"` → `AdId[0]`; a second board uses `AdId[1]` when enabled (`NUMAD > 1`). Calibration supports channels Ch.00–15 / Ch.16–31 switching.
- AO board: device name `"AIO001"` → `DaId[0]`.
- If device names differ, rename them in Device Manager (see README).

### Timer-driven execution model (critical)

All loops run from `CDigitShowBasicView::OnTimer`:

- **Timer 1** (fixed interval): acquisition loop — `AD_INPUT()` → `Cal_Physical()` / `Cal_Param()` → `ShowData()`.
- **Timer 2**: control feedback loop started by `Start_Control()`; dispatches by control number into `Control_DA()`; ends each cycle with explicit `DA_OUTPUT()`. `Stop_Control()` kills it.
- **Timer 3**: periodic data save (`SaveToFile()` / `SaveToFile2()`).

### Control mode dispatch

Control number selects the algorithm executed inside `CDigitShowBasicDoc::Control_DA()`. Implemented modes (methods in `DigitShowBasicDoc.h`):

| Mode family | Methods |
|---|---|
| Axial | `MonotonicAxialLoading`, `MonotonicAxialLoadingConstP`, `CyclicAxialLoading`, `SmallCyclicAxialLoading` |
| Torsional | `MonotonicTorsionalLoading`, `MonotonicTorsionalLoadingCNS`, `MonotonicTorsionalLoadingConstPA`, `CyclicTorsionalLoading`, `CyclicTorsionalLoadingCNS`, `SmallCyclicTorsionalLoading`, `SmallCyclicTorsionalLoadingCNS` |
| Path / others | `EffectiveStressPathLoading`, `Creep`, `FileControlableConsolidation` |

A control number of **0 must stop loading** — do not let new modes break that invariant.

### DA channel assignments (`ao` outputs, DA board)

| CH | Signal |
|---|---|
| CH00 | EP cell pressure |
| CH01 | Axial motor On/Off (0 V = On, 5 V = Off) |
| CH02 | Axial clutch |
| CH03 | Axial motor speed |
| CH04 | Torsion motor On/Off (0 V = On, 5 V = Off) |
| CH05 | Torsion clutch |
| CH06 | Torsion motor speed |

Channel indices live in `CH_Axis*` / `CH_Torsion*` members of `CDigitShowBasicDoc` (`DigitShowBasicDoc.cpp`). DA calibration factors per channel are set as `DA_Cal_a[]` / `DA_Cal_b[]` (e.g., torsion speed in V/RPM).

### AI channel assignments (`NameV[]` / `NameP[]`, up to 32 ch)

Primary board (typical wiring): CH0 vertical load [N], CH1 torque [Ncm], CH2/CH3 POT angles [rad], CH4 HCDPT effective stress [kPa], CH5 external LVDT, CH6 LDT1, CH8–CH10 CG gauges, CH11 LDT2, CH13 LCDPT volume change. CH16–31 belong to the optional second board.

`Cal_Physical()` converts all channels generically via calibration coefficients; `Cal_Param()` derives physical quantities from specific indices. If hardware wiring changes, update `Cal_Param()`, channel name tables in `DigitShowBasicDoc.cpp`, `Specimen.cpp`, `CalibrationFactor.cpp` labels, view headers, and `.rc` UI labels together. Existing `.cal` files key coefficients by channel index → rewiring requires recalibration.

### Torque membrane correction

`TorqueM` in `DigitShowBasicDoc.cpp` computes the membrane resistance torque from specimen inner/outer diameters and membrane modulus/thickness (`SpecimenData.MembraneModulus` / `MembraneThickness`). Only `TorqueM` is considered (Hashimoto, 2022.12.28). Keep this formula consistent with `Specimen.cpp` inputs.

## Key conventions for edits

1. **File encoding is UTF-8 with BOM (`EF BB BF`).** All `.cpp/.h/.rc/.rc2` files are saved as UTF-8 with BOM, and the resource files use `#pragma code_page(65001)` (including inside the TEXTINCLUDE sections). Do not save as Shift-JIS or without a BOM; editors that silently drop the BOM on "save" must not be used for these files. Verify the first three bytes are `0xEF 0xBB 0xBF` after editing.

2. **Do not write DA output directly from dialogs/control logic.** Control code updates `ctx->ao.raw[]` (in volts). Actual hardware writes happen in `DA_OUTPUT()` via the CAIO API.

3. **Board lifecycle safety:** boards are opened once (`AioInit`) and closed at exit; keep AO outputs zeroed before open/close where possible.

4. **`caio.lib` version must match the installed AIO-WDM driver.** `caio.lib` is a static import library calling `caio.dll` provided by the driver. The files in `src/` conform to **CONTEC API-AIO(WDM) Ver.9.20** (same as DigitShowBasic). If you upgrade the driver, replace `src/caio.lib` / `src/CAIO.H` with the ones from the new driver package; mismatches cause link errors or runtime crashes.

5. **Newer CONTEC drivers require an explicit AI scan clock.** Always call `AioSetAiScanClock()` with `floor(SamplingClock / enabled channel count)` µs (e.g., 1000 µs / 16 ch → 62 µs, rounded down to the safe side) *before* starting acquisition; the driver no longer derives it reliably from the sampling clock alone.

5. **No comments-in-code policy for new work is not enforced here** — this is legacy MFC code; match surrounding style instead.
