# Wind Viewer

## Compile

```bash
export LD_LIBRARY_PATH=/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH
gcc src/main.c -o build/wind-viewer -std=c11 -Idep/include -Ldep/lib -lraylib -lglfw -lGL -lm -lpthread -ldl -lrt -lX11
```
