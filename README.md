# zephyr-template

This is a template for Zephyr firmware app development that makes use of

- uv [(https://docs.astral.sh/uv/)](https://docs.astral.sh/uv/)
- poethepoet [(https://poethepoet.natn.io/index.html)](https://poethepoet.natn.io/index.html)

You would generally run commands via `uv` and `poe`

It is also a multi-project setup both for zephyr apps as well as other tools (e.g. python packages, libraries)
that could sit next to your firmware app(s).

The template has few board overlays for the app (Blinky) -

- ESP32 DevkitC V1
- nrf52832 DK
- native_sim (Linux Only)
- qemu_cortex_m3 (QEMU emulator on macOS)

> Note - Both of these are quite old boards but that is what I have to test with at the moment

The configured zephyr version in the manifest is `v4.3.0`

```bash
# setup your virtualenv
uv sync
```

```bash
# install pre-commit hooks
uv run pre-commit install
```

### Example / Conventions

```bash
# example when directly running west command
uv run west

# example when running some pre-configured commands/tasks via poe
uv run poe build-app
```

## Not changing v4.3.0 (the version set in west.yml of this repo)

In this mode, all you have to do is to issue following commands

Below steps are needed once or when you first clone the repo.

```bash
# do west update
uv run west update
```

```bash
# this would install the SDK corresponding to v4.3.0
uv run west sdk install
```

## Switching to another version of Zephyr

Below steps are needed rarely (as in when you modify the manifest [west.yml]) or when you first clone the repo.

### Step 1

```bash
# delete uv.lock
rm -rf uv.lock
# delete deps
rm -rf deps
```

### Step 2

Make a change in `west.yml` file for example change zephyr version and/or include modules that you need.

```bash
uv run west update
```

### Step 3

```bash
# this would install the SDK corresponding to your version of zephyr
uv run west sdk install
```

### Step 4

```bash
# This should update the dependencies (and uv.lock) as per your version of zephyr
uv add -r deps/zephyr/scripts/requirements.txt --dev
```

## Other commands

```bash
# See all the commands to run via poe
uv run poe
```

## VSCode workspace

The repo makes use of vscode workspace.

All the projects (`example-app` here) has settings.json that points to the generated header during it's build.

## Build firmware

Default board is `esp32_devkitc/esp32/procpu`

Note the usage of `--build-dir`. This would help isolate the build for various projects within the same repository.

```bash
uv run west build -b nrf52dk/nrf52832 -p always --build-dir builds/example-app example-app
uv run west build -b esp32_devkitc/esp32/procpu -p always --build-dir builds/example-app example-app
uv run west build -b native_sim -p always --build-dir builds/example-app example-app
uv run west build -b qemu_cortex_m3 -p always --build-dir builds/example-app example-app
```

## Flash

```bash
uv run west flash --build-dir builds/example-app
```

## Monitor (for esp32)

```bash
# cd to build directory
cd builds/example-app
uv run west espressif monitor
```
