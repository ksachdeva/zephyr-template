# AI Coding Assistant Context

This document provides necessary context for AI coding assistants (Claude Code, Gemini CLI, GitHub Copilot, OpenCode, etc.) regarding this repository.

## Repository Structure

```
├── .clang-format
├── .gitattributes
├── .gitignore
├── .pre-commit-config.yaml
├── .python-version
├── .venv
├── .vscode
│   ├── extensions.json
│   └── settings.json
├── .west
│   └── config
├── AGENTS.md
├── builds                  # The build directory
│   └── example-app
├── deps
│   ├── bootloader
│   ├── modules
│   ├── tools
│   └── zephyr
├── example-app             # Example app
│   ├── .gitignore
│   ├── .vscode
│   ├── boards
│   ├── CMakeLists.txt
│   ├── Kconfig
│   ├── prj.conf
│   └── src
├── LICENSE
├── poe.toml                # PoeThePoet tasks
├── pyproject.toml
├── README.md
├── uv.lock
└── west.yml
```


## Overview & Development Setup

This repository (named `zephyr-template`) has 1 project:
- example-app: A simple app that makes LED blink

The Zephyr based firmware development relies on `west` that not only wraps `cmake` build but also provide many other useful tools/commands.

This repository is configured to be a `uv` project. This means that by convention the virtualenv is at the root of the repository i.e. `.venv`.

Any time, there is a need to run any `python` app or tool including `west` commands, we must use `uv run` so that proper `virtualenv` is used.

The `poe.toml` file (used by `poethepoet` which is already installed in the virtual environment) contains reusable tasks that generally wrap other tools.

The `poe` tasks must be executed using `uv run poe`.

### Prohibited

You (the AI Agent) are not allowed to make changes to development setup files. Some examples file that belong to setup are listed below.

- poe.toml
- pyproject.toml
- uv.lock

You are not allowed to run `uv run poe west-setup` command. This command is intended to run once to download Zephyr OS and other modules
and is done by the repository author.


### Building

The repository provides few different ways to build, flash and monitor but not all token efficient.

When you (the AI Agent) is building the project use the below provided `poe` task

```bash
TAIL_S=5 TAIL_F=50 uv run poe agent-build-app
```

The above `poe` task
- Redirects the output to logs/example-app-build.log
- Does not pollute the context window as quite often last 5-10 lines of log should be sufficient
- TAIL_S=5 => last 5 lines if build is successful. Optional. Default is 5
- TAIL_F=50 => last 50 lines if build is unsuccessful. Optional. Default is 50

Remember -
If build failed, you would get `TAIL_F` number of lines but you also have access to `logs/example-app-build.log` so
your first attempt should not be to re-issue the build command with increased value for `TAIL_F` rather read the log file.
