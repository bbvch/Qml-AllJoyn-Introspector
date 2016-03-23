# QML AllJoyn Introspector

QML AllJoyn Introspector is an open source [AllJoyn](https://allseenalliance.org/framework)
client for discovering, introspecting, and controlling IoT devices on the local network. By
utilizing the Qt QML framework it can be run on multiple platforms. Basically, the supported
platforms are those supported by AllJoyn, i.e.

* Windows
* Android
* iOS
* OS X
* Linux


## Installation

* [Download and build](https://allseenalliance.org/framework/documentation/develop/building/) the AllJoyn framework, including at least "BINDINGS=cpp"
```bash
wget https://allseenalliance.org/releases/alljoyn/15.09/alljoyn-15.09.00a-src.tar.gz
tar xf alljoyn-15.09.00a-src.tar.gz
cd alljoyn-15.09.00a-src
scons BINDINGS=cpp
```
* Alternatively download a prebuilt AllJoyn framework
```bash
wget https://allseenalliance.org/releases/alljoyn/15.09/alljoyn-15.09.00a-android-sdk-rel.zip
unzip alljoyn-15.09.00a-android-sdk-rel.zip
```
* Set the following environment variables
```bash
export AJ_DIST=$PWD/core/alljoyn/build/linux/*/debug/dist
```
* Download and build AllJoyn-Introspector-Qml
```bash
git clone https://github.com/butzist/AllJoyn-Introspector-QML.git
cd AllJoyn-Introspector-QML
qmake
make
```

## Status

**Preview**

### Limitations:

* Only the string type (DBus type "s") is supported for method calls and properties
* Properties are read-only (and not tested yet)
