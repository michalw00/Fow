#include "core/core.h"

#define GAME

#ifdef GAME

int main() {
    fow::Core::Get().Start();
    return 0;
}
#endif // GAME

#ifdef EXPORTIMAGE

#include <raylib.h>
int main() {
    Image image = LoadImage("test.png");
    ExportImageAsCode(image, "test.h");
}
#endif // EXPORTIMAGE


