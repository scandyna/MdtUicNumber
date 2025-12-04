[[_TOC_]]

# Create Conan packages for MdtUicNumber libraries

Go to the root of the source tree:
```bash
conan create --version x.y.z --user scandyna --channel testing packaging/conan/$LIBRARY --profile:build $CONAN_PROFILE_BUILD --profile:host $CONAN_PROFILE_HOST --settings:build build_type=Release --settings:host build_type=$BUILD_TYPE --options:host "&:$OPTION=$OPTION_VALUE"
```
