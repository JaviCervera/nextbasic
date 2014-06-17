#ifndef GUITABBAR_H
#define GUITABBAR_H

#include "../common/defs.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void* CALL CreateTabBar(void* parent);
EXPORT void CALL AddTabBarItem(void* tabbar, void* item, const char* text);
EXPORT int CALL CountTabBarItems(void* tabbar);
EXPORT void CALL RemoveTabBarItem(void* tabbar, int index);
EXPORT void CALL SetTabBarIndex(void* tabbar, int index);
EXPORT int CALL TabBarIndex(void* tabbar);
EXPORT void CALL SetTabText(void* tabbar, int index, const char* text);
EXPORT const char* CALL TabText(void* tabbar, int index);
EXPORT void* CALL TabWidget(void* tabbar, int index);

#ifdef __cplusplus
}
#endif

#endif // GUITABBAR_H