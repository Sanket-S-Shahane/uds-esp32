# Notes - uds-esp32

## Day 3 - Wed Apr 29, 2026

### ESP-IDF setup
- Version: v5.5.4 (current stable)
- Path: C:\esp\v5.5.4\esp-idf
- v6.0.1 install kept failing — switched to v5.5.4 via Expert Install, succeeded
- Lesson: stick to current stable, not latest. Latest is for trailblazers.

### VS Code workflow (no F1 menu needed)
- Bottom status bar has all the controls: target, port, flame icon (Build/Flash/Monitor)
- Exit serial monitor: Ctrl+]
- First build takes 3-6 min (compiles FreeRTOS + drivers from scratch). Subsequent builds are seconds.

### Phase 1 verification: blink example
- Built and flashed successfully on COM9
- Serial output confirms firmware running and toggling GPIO every 1s
- Onboard LED on DOIT DevKit V1 is GPIO 2, not GPIO 5 (board variant difference)
- This is expected — we're using GPIO 5 for CAN TX anyway

### TWAI vs CAN
- ESP32 calls its CAN peripheral "TWAI" (Two-Wire Automotive Interface) for trademark reasons
- Functionally identical to CAN 2.0B
- Driver header: driver/twai.h

### Hardware wiring (Phase 3)
- 3V3 → VCC (NOT 5V — SN65HVD230 is a 3.3V transceiver, 5V will damage it)
- GND → GND
- GPIO 5 (D5) → CTX/TXD (MCU TX → transceiver TX-input)
- GPIO 4 (D4) → CRX/RXD (MCU RX ← transceiver RX-output)
- CANH/CANL: not connected (loopback test tomorrow doesn't need physical bus)
- Always wire with power off

### Repo structure decisions
- Repo on E:\Sanket_code_backups\GitHub\uds-esp32 (E: drive — more space)
- ESP-IDF projects can be huge (~200-500MB build folder). Added build/ to .gitignore.
- LICENSE: MIT
- README + NOTES + .gitignore committed in first push

### Things I almost messed up
- [Add anything that confused you, you almost wired wrong, or learned the hard way]

## Day 4 - Mon May 4, 2026 - Cleanup

Restored repo after Thursday's xcopy mess.

Commands learned:
- git checkout HEAD -- filename → restore a file from last commit
- del filename → delete a file
- Remove-Item -Recurse -Force foldername → delete a folder

Lesson: stop when confused. Pushing through commands made the mess worse on Thursday. Stopping and asking saved me 30+ minutes today.

Lesson 2: ALWAYS run git status before git add. Today I added Day 4 notes to README.md by mistake instead of NOTES.md. git status showed me the truth — `modified: README.md` instead of `modified: NOTES.md`. I had to use git checkout HEAD -- README.md again to undo it.

## Day 5 - Tue May 5, 2026 - PowerShell basics

### What I learned
I learned Power Shell commands,
1) pwd : which means print working directory
2) dir : give the list of files or folders in the directory
3) cat : also gives the list of the files or folders in the directory
4) type : is use to read the conetent in the file
5) cd  : is used to change the path its long form is change directory
6) del filename : is used to delete the file
7) Remove-Item -Recurse -Force foldername : is used to delete the folder with the all contenet in that folder like files, subfolder even files from subfolder 


### Commands to remember
- pwd → Print Working Directory (where am I?)
- dir / cat / type → list folder / read file
- cd / cd .. / cd ~ → navigate
- del filename → delete a file
- Remove-Item -Recurse -Force foldername → delete folder + contents

### Path concept
Absolute path: starts from a drive letter, works from anywhere. Example: E:\Sanket_code_backups\GitHub\uds-esp32\NOTES.md
Relative path: starts from where you currently are. Example: if you're already in uds-esp32, then NOTES.md alone is a relative path that points to the same file.

### Subtle quirks worth remembering
- cd C: vs cd C:\ behave differently
- Empty output from dir = empty folder (NOT a bug)
- File created via Out-File is UTF-16 (size larger than expected)
- No Recycle Bin in PowerShell deletes — verify path before pressing Enter
- To write UTF-8 in PowerShell: use `Add-Content` or `Set-Content` (UTF-8 by default), or `Out-File -Encoding utf8`. Check version: $PSVersionTable.PSVersion.

### Today's mistake / lesson
file size created was UTF-16 and needed UTF-8

## Day 6 - Wed May 6, 2026 - Copying and moving files

### What I learned today
Today I learn aboute the copy pate files, folders as well as moving the files folders also important note there must be source and destination location in command

### The commands I used today
For each, write what it does in your own words:
- Copy-Item source dest → it compies the item from source into destination, keeping source item intact
- Copy-Item -Recurse source dest → it copies folder with all files sunfolder and files under subfolder to destination location
- Move-Item source dest → it moves the item from source to destination its like chnaging the path of the Item
- Move-Item used for renaming → move item is like changing the path of old file and making the new so even its like the renaming as well

### The universal rule for copy and move
Every copy or move command requires what?
must have source address as well as destination address

### Why Friday's xcopy failed (compared to today's success)
the destination address was missing

### Mistakes today
None

## Day 7 - Thu May 7, 2026 - Git deep dive

### What clicked today
Working directory — files on disk, means the files which are in the working directory
Staging area — changes about to be committed (after git add), changes which are staged meand after git add
Repository — committed snapshots (after git commit), repsository is dtored on git where the data is committed

### The four states a file can be in
Untracked — file exists on disk, Git doesn't know about it yet (new file Git has never seen), means the new files or the file which never added or nvere been on repository
Modified (working dir) — file is tracked, has changes not yet staged, means the alredy available file changed
Staged — changes are in staging, ready to commit (after git add), means changed file has been added and now we can commit it to repository
Committed — changes saved in repository as a snapshot (after git commit), means the chnaged file or files on working directory has been committed to repository

### New commands I used today
- git diff [file] → it shows the what changed in file
- git log --oneline → it shows chain of commits or can say details of commit
- git show [hash] → it shows full details of that partiular commit

### Encoding gotcha
Git required UTF-8 file if we generate or change the file from power shell it is in format of UTF-16

### Lesson I want to remember
the boxes or can say position of files

## Day 8 - Fri May 8, 2026 - Git error recovery

### The four "I want to undo" situations
1) When I made the changes in any file now I want to undo the changes use git restore
2) When I made the changes in any file and did git add now I want to undo the changes use git restore --staged
3) When I made the changes in any file and did git add  also commited the file now I want to undo the changes use first use git reset --soft HEAD~1then use restore --staged or can directlu use git reset --hard HEAD~1 
4) When I made a changes and committed it now i want to undo thoses changes with comment then use git revert

[Write them in your own words — what's the situation in each, what command fixes it]

### Recovery commands I used today
- git restore [file] → Restores the working directory version of the file from the last commit (discard local unstaged changes in that file)
- git restore --staged [file] → Removes the file from the staging area (git add) but keeps the actual file changes in your working directory
- git reset --soft HEAD~1 → Moves HEAD back by one commit, but keeps all changes staged 
- git reset --hard HEAD~1 → Removes the last commit AND deletes all associated working directory/staged changes permanently
- git revert [hash] → Creates a new commit that undoes the changes introduced by a specific commit
- git reflog → Shows the history of where HEAD and branch pointers moved

### The most important rule
Think twice before using git reset --hard HEAD~1

### Encoding gotcha I saw again today
Git treates the UTF-16 file as a binary so always the file content should be UTF-8 format

### Lesson for myself
if any changes is done and added or commited to repository even though restores back to normal still kind hide whatever we have done because of git reflog 

## Day 11 - Monday May 11, 2026 - ESP‑IDF Project Structure Deep Dive

### Why we studied this
To understand every file in an ESP-IDF project so I can navigate any example or open‑source project, and to prepare for adding my own CAN driver next week.

### What I learned
1. Two CMakeLists.txt files
- Top‑level `CMakeLists.txt` (root folder): boilerplate – sets project name, includes ESP‑IDF's `project.cmake`, enables minimal build. Does NOT list source files.
- `main/CMakeLists.txt`: calls `idf_component_register(SRCS "file.c" INCLUDE_DIRS ".")`. Every `.c` file must be in `SRCS`; `INCLUDE_DIRS` tells where header files are (`.` = current folder).

2. Structure of `blink_example_main.c`
- Includes: `<stdio.h>` (standard C), `"freertos/FreeRTOS.h"`, `"driver/gpio.h"`, `"esp_log.h"`, `"sdkconfig.h"` (auto‑generated from menuconfig).
- Configuration defines: `#define BLINK_GPIO CONFIG_BLINK_GPIO` – makes pin changeable via menuconfig without editing C code.
- Static module variable: `static uint8_t s_led_state = 0;` – holds current LED state, private to this file.
- Helper functions (`static`):
  - `configure_led()`: runs once. Calls `gpio_reset_pin()` (defensive init) then `gpio_set_direction(..., GPIO_MODE_OUTPUT)`.
  - `blink_led()`: runs every loop. Calls `gpio_set_level(BLINK_GPIO, s_led_state)`.
- `app_main()`: entry point called by ESP‑IDF startup. Pattern:
  ```
  configure_led();            // one‑time
  while (1) {
      blink_led();            // action
      s_led_state = !s_led_state;  // toggle state
      vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
  }'''
3. FreeRTOS delay vs blocking delay

vTaskDelay() yields CPU to FreeRTOS – other tasks can run, watchdog doesn't trip.

Bare‑metal for‑loop delay blocks everything, causes watchdog resets – never use in ESP‑IDF.

4. Three configuration files

sdkconfig.defaults: written by user, committed to Git. Sets default config values for fresh builds.

sdkconfig: auto‑generated, gitignored. Holds current menuconfig choices. Changes when you run idf.py menuconfig.

sdkconfig.h: auto‑generated from sdkconfig during build. Contains #define CONFIG_* macros. Included in C code – never edited manually.

Chip‑specific overrides: sdkconfig.defaults.esp32, sdkconfig.defaults.esp32s3, etc. allow one project to run on different ESP32 variants.


### Commands / code I used

cd E:\Sanket_code_backups\GitHub\idf_blink_test
pwd
dir
code CMakeLists.txt
code main/CMakeLists.txt
code main/blink_example_main.c
type sdkconfig.defaults
Key code patterns:

c
// Static function – private to this file
static void configure_led(void) { ... }

// Using config macro
#define BLINK_GPIO CONFIG_BLINK_GPIO

// vTaskDelay with milliseconds
vTaskDelay(1000 / portTICK_PERIOD_MS);  // 1 second delay

// Toggle state
s_led_state = !s_led_state;

### Mistakes / things that confused me
Static functions: I thought static meant "can be called from anywhere". It actually means private to this file (encapsulation). Non‑static functions are visible across the whole project.

File scope vs function scope: I didn't understand why s_led_state was outside app_main(). The reason: both app_main() and blink_led() need to access it. File scope makes it visible to all functions in the file.

The three config files: I initially confused sdkconfig.defaults (user‑written, in Git) with sdkconfig (auto‑generated, gitignored). Now I know: .defaults = starting defaults; sdkconfig = current state.


### One thing to remember
Always use vTaskDelay() in ESP‑IDF. Never use a busy‑loop delay (for (int i=0; i<1000000; i++);) – it blocks the whole system and will cause a watchdog timeout. vTaskDelay() yields the CPU so FreeRTOS can run other tasks.

## Day 12 - Tue May 12, 2026 - menuconfig hands-on

### Why we studied this
menuconfig is the tool I will use to enable the TWAI/CAN driver and configure its baud rate, filters, and pin assignments next week. Today I learned how to open it, change a setting, save, rebuild, and see the effect on hardware – the exact workflow for configuring any ESP‑IDF driver.

### What I learned
- **menuconfig is a text‑based configuration menu** (blue screen, keyboard only). It lets me change settings without editing C code.
- **Navigation keys**: arrows (move), Enter (enter submenu), Space (toggle checkboxes), `/` (search), `S` (save), `Q` (quit).
- **The config chain** :
  - Change `Blink GPIO number` from 5 to 2 in `Example Configuration`.
  - Save to `sdkconfig` (auto‑generated, gitignored).
  - `idf.py build` generates `sdkconfig.h` with `#define CONFIG_BLINK_GPIO 2`.
  - The C macro `#define BLINK_GPIO CONFIG_BLINK_GPIO` picks up the value.
  - `gpio_set_level()` drives GPIO 2 → onboard LED blinks.
- **Plain PowerShell vs ESP‑IDF terminal**: `idf.py` only works in the terminal where the environment variables and Python venv are loaded. The prompt shows `(venv)` when it's active.
- **Select‑String** is PowerShell’s equivalent of `grep` – used to verify config changes inside `sdkconfig`.

### Commands / code I used


cd E:\Sanket_code_backups\GitHub\idf_blink_test
idf.py --version                     # confirm environment
idf.py set-target esp32              # set chip (triggers fullclean)
idf.py menuconfig                    # open the blue config menu
# Inside menuconfig: ↓ to Example Configuration → Enter → ↓ to (5) Blink GPIO number → Enter → type 2 → Enter → S (save) → Enter → Q (quit)
Select-String "CONFIG_BLINK_GPIO" sdkconfig   # verify value in file
idf.py build                         # compile with new config
idf.py -p COM9 flash                 # flash to ESP32
idf.py -p COM9 monitor               # view serial output
# Exit monitor: Ctrl+] 


### Mistakes / things that confused me
Saving twice: I saved, then later pressed S again. menuconfig said "no changes to save" – We thought the setting was lost, but it was already saved. The message just means nothing new to write.

Plain terminal vs ESP‑IDF terminal: I first ran idf.py in a normal PowerShell and got not recognized. I learned to look for the (venv) prompt – that’s the signal the environment is loaded.


### One thing to remember
The entire configuration chain is: menuconfig → sdkconfig → sdkconfig.h → C macro → hardware. Changing a single number in the blue menu and saving propagates all the way to the physical pin. This is how I will enable and configure the CAN driver next week without touching C code.