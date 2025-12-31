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

```bash
# example when directly running west command
uv run west

# example when running some pre-configured commands/tasks via poe
uv run poe build-app
```

The configured zephyr version in the manifest is `v4.3.0`

```bash
# Step 1
# setup your virtualenv
uv sync
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

### Build firmware 

Default board is `esp32_devkitc/esp32/procpu`

```bash
uv run poe build-app -b nrf52dk/nrf52832 -p always
uv run poe build-app -b esp32_devkitc/esp32/procpu -p always
uv run poe build-app -b native_sim -p always
uv run poe build-app -b qemu_cortex_m3 -p always
```

### Flash

```bash
uv run poe flash-app
```