#!/usr/bin/env bash

# init submodulewho was not fetch
git submodule update --init --recursive

# stock project directory
PROJECT_DIR=$(pwd)/

DEPENDENCIES_DIR="dependencies/"

# install mongo-c-driver
