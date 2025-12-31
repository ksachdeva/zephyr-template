# zephyr-template

This is a template for Zephyr firmware app development that makes use of 

- uv [(https://docs.astral.sh/uv/)](https://docs.astral.sh/uv/)
- poethepoet [(https://poethepoet.natn.io/index.html)](https://poethepoet.natn.io/index.html)

You would generally run commands via `uv` and `poe`

It is also a multi-project setup both for zephyr apps as well as other tools (e.g. python packages, libraries)
that could sit next to your firmware app(s).


```bash
# example when directly running west command
uv run west

# example when running west and/or other apps via poe
uv run poe build-app
```

The configured zephyr version in the manifest is `v4.3.0`

```bash
# Step 1
# setup your virtualenv
uv sync
```

## Not changing v4.3.0

In this mode, all you have to do is to issue following commands

```bash
# do west update
uv run poe west-update
```

## Switching to another version of Zephyr

Make a change in `west.yml` file

```bash
# Step 1
# delete uv.lock
rm -rf uv.lock 
# delete deps
rm -rf deps
```

```bash
# Step 2
uv run poe west-update
```

```bash
# Step 3
# This should update the dependencies (and uv.lock) as per your version of zephyr
uv add -r deps/zephyr/scripts/requirements.txt --dev
```

## Other commands

```bash
# See all the commands to run via poe
uv run poe
```