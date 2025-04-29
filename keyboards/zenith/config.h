#pragma once

#define DEBOUNCE        5
#define USB_VID         0xFEED
#define USB_PID         0x6060
#define MATRIX_ROWS     9
#define MATRIX_COLS     12
#define PRODUCT_ID      0x1234

/* Wiring of rows and columns to physical pins */
/* Placeholder — update later with your real wiring */
#define MATRIX_ROW_PINS { GP0, GP1, GP2, GP3, GP4, GP5, GP6, GP7, GP8 }
#define MATRIX_COL_PINS { GP9, GP10, GP11, GP12, GP13, GP14, GP15, GP16, GP17, GP18, GP19, GP20 }

/* Mechanical locking support */
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
