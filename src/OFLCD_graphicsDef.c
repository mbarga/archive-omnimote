/* Graphical elements library */

#ifndef __OmnimoteFoundation
#include "OmnimoteFoundation.h"
#endif

/*
extern const BYTE OFSignal0H[4][30];
extern const BYTE OFSignal0V[4][30];
extern const BYTE OFSignal1H[4][30];
extern const BYTE OFSignal1V[4][30];
extern const BYTE OFSignal2H[4][30];
extern const BYTE OFSignal2V[4][30];
extern const BYTE OFSignal3H[4][30];
extern const BYTE OFSignal3V[4][30];
extern const BYTE OFSignal4H[4][30];
extern const BYTE OFSignal4V[4][30];
extern const BYTE OFSignal5H[4][30];
extern const BYTE OFSignal5V[4][30];
extern const BYTE OFLetterRH[4][30];
extern const BYTE OFLetterRV[4][30];
extern const BYTE OFLetterEH[4][30];
extern const BYTE OFLetterEV[4][30];
extern const BYTE OFLetterOH[4][30];
extern const BYTE OFLetterOV[4][30];
extern const BYTE OFLetterCH[4][30];
extern const BYTE OFLetterCV[4][30];
extern const BYTE OFLetterKH[4][30];
extern const BYTE OFLetterKV[4][30];
extern const BYTE OFLetterUH[4][30];
extern const BYTE OFLetterUV[4][30];
extern const BYTE OFLetterBH[4][30];
extern const BYTE OFLetterBV[4][30];
extern const BYTE OFLetterHH[4][30];
extern const BYTE OFLetterHV[4][30];
extern const BYTE OFLetterNH[4][30];
extern const BYTE OFLetterNV[4][30];
extern const BYTE OFLetterYH[4][30];
extern const BYTE OFLetterYV[4][30];
extern const BYTE OFLetterSH[4][30];
extern const BYTE OFLetterSV[4][30]; */

#define OFSignalNull {{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	 /
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,			 /
0x00,	0x00,	0x00	},																																			 /
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,			 /	
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	 /	
0x00,	0x00,	0x00	},																																/
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,		 /
																																										 /
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	 /
																																											/
0x00,	0x00,	0x00	},																																	 /
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,				 /
																																												/
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,			/
																																												 /
0x00,	0x00,	0x00	}}

const BYTE OFSignal0H[4][30] = {{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	0x80,	0x80,	0x80,	0x80,	0x00,	0xFE,	0x02,	

0x02,	0x02,	0xFE	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0xE0,	0x20,	0x20,	0x20,	0xE0,	0x00,	0xFF,	0x00,	0x00,	0x00,	0xFF,	0x00,	0xFF,	0x00,	

0x00,	0x00,	0xFF	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xF8,	0x08,	0x08,	0x08,	0xF8,	0x00,	

0xFF,	0x00,	0x00,	0x00,	0xFF,	0x00,	0xFF,	0x00,	0x00,	0x00,	0xFF,	0x00,	0xFF,	0x00,	

0x00,	0x00,	0xFF	},
{	0x00,	0x7E,	0x42,	0x42,	0x42,	0x7E,	0x00,	0x7F,	0x40,	0x40,	0x40,	0x7F,	0x00,	

0x7F,	0x40,	0x40,	0x40,	0x7F,	0x00,	0x7F,	0x40,	0x40,	0x40,	0x7F,	0x00,	0x7F,	0x40,	

0x40,	0x40,	0x7F	}};

const BYTE OFSignal0V[4][30] = {{	0x3E,	0x22,	0x22,	0x22,	0x22,	0x22,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	

0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	

0xA2,	0xA2,	0xBE	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x0F,	0x08,	0x08,	0x08,	0x08,	0x08,	0xE8,	

0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	

0x28,	0x28,	0xEF	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x03,	

0x02,	0x02,	0x02,	0x02,	0x02,	0xFA,	0x8A,	0x8A,	0x8A,	0x8A,	0x8A,	0x8A,	0x8A,	0x8A,	

0x8A,	0x8A,	0xFB	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x3E,	0x22,	0x22,	

0x22,	0x22,	0x3E	}};

const BYTE OFSignal1H[4][30] = {{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	0x80,	0x80,	0x80,	0x80,	0x00,	0xFE,	0x02,	

0x02,	0x02,	0xFE	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0xE0,	0x20,	0x20,	0x20,	0xE0,	0x00,	0xFF,	0x00,	0x00,	0x00,	0xFF,	0x00,	0xFF,	0x00,	

0x00,	0x00,	0xFF	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xF8,	0x08,	0x08,	0x08,	0xF8,	0x00,	

0xFF,	0x00,	0x00,	0x00,	0xFF,	0x00,	0xFF,	0x00,	0x00,	0x00,	0xFF,	0x00,	0xFF,	0x00,	

0x00,	0x00,	0xFF	},
{	0x00,	0x7E,	0x7E,	0x7E,	0x7E,	0x7E,	0x00,	0x7F,	0x40,	0x40,	0x40,	0x7F,	0x00,	

0x7F,	0x40,	0x40,	0x40,	0x7F,	0x00,	0x7F,	0x40,	0x40,	0x40,	0x7F,	0x00,	0x7F,	0x40,	

0x40,	0x40,	0x7F	}};

const BYTE OFSignal1V[4][30] = {{	0x3E,	0x22,	0x22,	0x22,	0x22,	0x22,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	

0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	

0xA2,	0xA2,	0xBE	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x0F,	0x08,	0x08,	0x08,	0x08,	0x08,	0xE8,	

0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	

0x28,	0x28,	0xEF	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x03,	

0x02,	0x02,	0x02,	0x02,	0x02,	0xFA,	0x8A,	0x8A,	0x8A,	0x8A,	0x8A,	0x8A,	0x8A,	0x8A,	

0x8A,	0x8A,	0xFB	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x3E,	0x3E,	0x3E,	

0x3E,	0x3E,	0x3E	}};

const BYTE OFSignal2H[4][30] = {{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	0x80,	0x80,	0x80,	0x80,	0x00,	0xFE,	0x02,	

0x02,	0x02,	0xFE	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0xE0,	0x20,	0x20,	0x20,	0xE0,	0x00,	0xFF,	0x00,	0x00,	0x00,	0xFF,	0x00,	0xFF,	0x00,	

0x00,	0x00,	0xFF	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0x00,	

0xFF,	0x00,	0x00,	0x00,	0xFF,	0x00,	0xFF,	0x00,	0x00,	0x00,	0xFF,	0x00,	0xFF,	0x00,	

0x00,	0x00,	0xFF	},
{	0x00,	0x7E,	0x7E,	0x7E,	0x7E,	0x7E,	0x00,	0x7F,	0x7F,	0x7F,	0x7F,	0x7F,	0x00,	

0x7F,	0x40,	0x40,	0x40,	0x7F,	0x00,	0x7F,	0x40,	0x40,	0x40,	0x7F,	0x00,	0x7F,	0x40,	

0x40,	0x40,	0x7F	}};

const BYTE OFSignal2V[4][30] = {{	0x3E,	0x22,	0x22,	0x22,	0x22,	0x22,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	

0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	

0xA2,	0xA2,	0xBE	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x0F,	0x08,	0x08,	0x08,	0x08,	0x08,	0xE8,	

0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	

0x28,	0x28,	0xEF	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x03,	

0x02,	0x02,	0x02,	0x02,	0x02,	0xFA,	0xFA,	0xFA,	0xFA,	0xFA,	0xFA,	0xFA,	0xFA,	0xFA,	

0xFA,	0xFA,	0xFB	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x3E,	0x3E,	0x3E,	

0x3E,	0x3E,	0x3E	}};

const BYTE OFSignal3H[4][30] = {{	0x3E,	0x22,	0x22,	0x22,	0x22,	0x22,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	

0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	

0xA2,	0xA2,	0xBE	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x0F,	0x08,	0x08,	0x08,	0x08,	0x08,	0xE8,	

0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	0x28,	

0x28,	0x28,	0xEF	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x03,	

0x02,	0x02,	0x02,	0x02,	0x02,	0xFA,	0xFA,	0xFA,	0xFA,	0xFA,	0xFA,	0xFA,	0xFA,	0xFA,	

0xFA,	0xFA,	0xFB	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x3E,	0x3E,	0x3E,	

0x3E,	0x3E,	0x3E	}};

const BYTE OFSignal3V[4][30] = {{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	0x80,	0x80,	0x80,	0x80,	0x00,	0xFE,	0x02,	

0x02,	0x02,	0xFE	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0x00,	0xFF,	0x00,	0x00,	0x00,	0xFF,	0x00,	0xFF,	0x00,	

0x00,	0x00,	0xFF	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0x00,	

0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x00,	0xFF,	0x00,	0x00,	0x00,	0xFF,	0x00,	0xFF,	0x00,	

0x00,	0x00,	0xFF	},
{	0x00,	0x7E,	0x7E,	0x7E,	0x7E,	0x7E,	0x00,	0x7F,	0x7F,	0x7F,	0x7F,	0x7F,	0x00,	

0x7F,	0x7F,	0x7F,	0x7F,	0x7F,	0x00,	0x7F,	0x40,	0x40,	0x40,	0x7F,	0x00,	0x7F,	0x40,	

0x40,	0x40,	0x7F	}};

const BYTE OFSignal4H[4][30] = {{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	0x80,	0x80,	0x80,	0x80,	0x00,	0xFE,	0x02,	

0x02,	0x02,	0xFE	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x00,	0xFF,	0x00,	

0x00,	0x00,	0xFF	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0x00,	

0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x00,	0xFF,	0x00,	

0x00,	0x00,	0xFF	},
{	0x00,	0x7E,	0x7E,	0x7E,	0x7E,	0x7E,	0x00,	0x7F,	0x7F,	0x7F,	0x7F,	0x7F,	0x00,	

0x7F,	0x7F,	0x7F,	0x7F,	0x7F,	0x00,	0x7F,	0x7F,	0x7F,	0x7F,	0x7F,	0x00,	0x7F,	0x40,	

0x40,	0x40,	0x7F	}};

const BYTE OFSignal4V[4][30] = {{	0x3E,	0x22,	0x22,	0x22,	0x22,	0x22,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	

0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	0xA2,	

0xA2,	0xA2,	0xBE	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x0F,	0x0F,	0x0F,	0x0F,	0x0F,	0x0F,	0xEF,	

0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	

0xEF,	0xEF,	0xEF	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x03,	

0x03,	0x03,	0x03,	0x03,	0x03,	0xFB,	0xFB,	0xFB,	0xFB,	0xFB,	0xFB,	0xFB,	0xFB,	0xFB,	

0xFB,	0xFB,	0xFB	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x3E,	0x3E,	0x3E,	

0x3E,	0x3E,	0x3E	}};

const BYTE OFSignal5H[4][30] = {{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	0x80,	0x80,	0x80,	0x80,	0x00,	0xFE,	0xFE,	

0xFE,	0xFE,	0xFE	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x00,	0xFF,	0xFF,	

0xFF,	0xFF,	0xFF	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0x00,	

0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x00,	0xFF,	0xFF,	

0xFF,	0xFF,	0xFF	},
{	0x00,	0x7E,	0x7E,	0x7E,	0x7E,	0x7E,	0x00,	0x7F,	0x7F,	0x7F,	0x7F,	0x7F,	0x00,	

0x7F,	0x7F,	0x7F,	0x7F,	0x7F,	0x00,	0x7F,	0x7F,	0x7F,	0x7F,	0x7F,	0x00,	0x7F,	0x7F,	

0x7F,	0x7F,	0x7F	}};

const BYTE OFSignal5V[4][30] = {{	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0xBE,	0xBE,	0xBE,	0xBE,	0xBE,	

0xBE,	0xBE,	0xBE,	0xBE,	0xBE,	0xBE,	0xBE,	0xBE,	0xBE,	0xBE,	0xBE,	0xBE,	0xBE,	

0xBE,	0xBE,	0xBE,	0xBE,	0xBE,	0xBE	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x0F,	0x0F,	0x0F,	0x0F,	0x0F,	0x0F,	0xEF,	

0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	0xEF,	

0xEF,	0xEF,	0xEF	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x03,	

0x03,	0x03,	0x03,	0x03,	0x03,	0xFB,	0xFB,	0xFB,	0xFB,	0xFB,	0xFB,	0xFB,	0xFB,	0xFB,	

0xFB,	0xFB,	0xFB	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x3E,	0x3E,	0x3E,	

0x3E,	0x3E,	0x3E	}};

const BYTE OFLetterRH[4][30] = {{	0x00,	0x00,	0xFE,	0xFE,	0xFE,	0xFE,	0xFE,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	

0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x7E,	0xFC,	0xFC,	0xFC,	0xF8,	0xF0,	0xC0,	

0x00,	0x00,	0x00,	0x00	},
{	0x00,	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	

0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xF0,	0xF8,	0xFF,	0xFF,	0x7F,	0x3F,	0x0F,	0x00,	

0x00,	0x00,	0x00	},
{	0x00,	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	

0x03,	0x03,	0x03,	0x07,	0x1F,	0x7F,	0xFD,	0xFD,	0xF8,	0xF0,	0xE0,	0x80,	0x00,	0x00,	

0x00,	0x00,	0x00	},
{	0x00,	0x00,	0x7F,	0x7F,	0x7F,	0x7F,	0x7F,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x01,	0x07,	0x1F,	0x7F,	0x7F,	0x7F,	0x7C,	0x70,	

0x40,	0x00,	0x00	}};

const BYTE OFLetterRV[4][30] = {{	0x00,	0x00,	0x80,	0xC0,	0xC0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xC0,	

0xC0,	0x80,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	0x80,	0xC0,	0xC0,	0xC0,	0xE0,	

0xE0,	0xF0,	0xF0,	0xF8	},
{	0xF8,	0xFF,	0xFF,	0xFF,	0xFF,	0x0F,	0x07,	0x03,	0x03,	0x03,	0x07,	0x0F,	0xFF,	

0xFF,	0xFF,	0xFC,	0xF0,	0x7C,	0x3E,	0x3F,	0x1F,	0x1F,	0x0F,	0x0F,	0x07,	0x07,	0x03,	

0x03,	0x01,	0x01	},
{	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xFF,	

0xFF,	0xFF,	0xFF,	0xFF,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00	},
{	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	

0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	

0x1F,	0x1F,	0x1F	}};

const BYTE OFLetterEH[4][30] = {{	0x00,	0x00,	0x00,	0x00,	0xFC,	0xFC,	0xFC,	0xFC,	0xFC,	0x7C,	0x7C,	0x7C,	

0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	

0x00,	0x00,	0x00,	0x00	},
{	0x00,	0x00,	0x00,	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xE0,	0xE0,	0xE0,	0xE0,	

0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00	},
{	0x00,	0x00,	0x00,	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x03,	0x03,	0x03,	0x03,	

0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00	},
{	0x00,	0x00,	0x00,	0x00,	0x3F,	0x3F,	0x3F,	0x3F,	0x3F,	0x3E,	0x3E,	0x3E,	0x3E,	

0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x00,	

0x00,	0x00,	0x00	}};

const BYTE OFLetterEV[4][30] = {{	0x00,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xE0,	0xE0,	

0xE0,	0xE0,	0xE0,	0x00	},
{	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xFE,	

0xFE,	0xFE,	0xFE,	0xFE,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xFF,	0xFF,	0xFF,	

0xFF,	0xFF,	0x00	},
{	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xC0,	0xC0,	0xC0,	0xC0,	0xC0,	0xC0,	0xFF,	

0xFF,	0xFF,	0xFF,	0xFF,	0xC0,	0xC0,	0xC0,	0xC0,	0xC0,	0xC0,	0xC0,	0xFF,	0xFF,	0xFF,	

0xFF,	0xFF,	0x00	},
{	0x00,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	

0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	

0x07,	0x07,	0x00	}};

const BYTE OFLetterOH[4][30] = {{	0x00,	0x00,	0x00,	0xC0,	0xE0,	0xF0,	0xF0,	0xF8,	0xF8,	0xFC,	0x7C,	0x7C,	

0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0xFC,	0xF8,	0xF8,	0xF0,	0xF0,	0xE0,	

0xC0,	0x00,	0x00,	0x00	},
{	0x00,	0xFC,	0xFF,	0xFF,	0xFF,	0xFF,	0x07,	0x01,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x01,	0x07,	0xFF,	0xFF,	0xFF,	

0xFF,	0xFC,	0x00	},
{	0x00,	0x3F,	0xFF,	0xFF,	0xFF,	0xFF,	0xE0,	0x80,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	0xE0,	0xFF,	0xFF,	0xFF,	

0xFF,	0x3F,	0x00	},
{	0x00,	0x00,	0x00,	0x03,	0x07,	0x0F,	0x0F,	0x1F,	0x1F,	0x3F,	0x3E,	0x3E,	0x3E,	

0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3F,	0x1F,	0x1F,	0x0F,	0x0F,	0x07,	0x03,	

0x00,	0x00,	0x00	}};

const BYTE OFLetterOV[4][30] = {{	0x00,	0x00,	0x00,	0xC0,	0xE0,	0xF0,	0xF0,	0xF8,	0xF8,	0xFC,	0x7C,	0x7C,	

0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0xFC,	0xF8,	0xF8,	0xF0,	0xF0,	0xE0,	

0xC0,	0x00,	0x00,	0x00	},
{	0x00,	0xFC,	0xFF,	0xFF,	0xFF,	0xFF,	0x07,	0x01,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x01,	0x07,	0xFF,	0xFF,	0xFF,	

0xFF,	0xFC,	0x00	},
{	0x00,	0x3F,	0xFF,	0xFF,	0xFF,	0xFF,	0xE0,	0x80,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	0xE0,	0xFF,	0xFF,	0xFF,	

0xFF,	0x3F,	0x00	},
{	0x00,	0x00,	0x00,	0x03,	0x07,	0x0F,	0x0F,	0x1F,	0x1F,	0x3F,	0x3E,	0x3E,	0x3E,	

0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3F,	0x1F,	0x1F,	0x0F,	0x0F,	0x07,	0x03,	

0x00,	0x00,	0x00	}};

const BYTE OFLetterCH[4][30] = {{	0x00,	0x00,	0x00,	0xC0,	0xE0,	0xF0,	0xF0,	0xF8,	0xF8,	0xFC,	0x7C,	0x7C,	

0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0xFC,	0xF8,	0xF8,	0xF0,	0xF0,	0xE0,	

0xC0,	0x00,	0x00,	0x00	},
{	0x00,	0xFC,	0xFF,	0xFF,	0xFF,	0xFF,	0x07,	0x01,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x01,	0x03,	0x03,	0x03,	0x03,	

0x03,	0x00,	0x00	},
{	0x00,	0x3F,	0xFF,	0xFF,	0xFF,	0xFF,	0xE0,	0x80,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	0xC0,	0xC0,	0xC0,	0xC0,	

0xC0,	0x00,	0x00	},
{	0x00,	0x00,	0x00,	0x03,	0x07,	0x0F,	0x0F,	0x1F,	0x1F,	0x3F,	0x3E,	0x3E,	0x3E,	

0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3F,	0x1F,	0x1F,	0x0F,	0x0F,	0x07,	0x03,	

0x00,	0x00,	0x00	}};

const BYTE OFLetterCV[4][30] = {{	0x00,	0x00,	0x00,	0xC0,	0xE0,	0xF0,	0xF0,	0xF8,	0xF8,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xF8,	0xF8,	0xF0,	0xF0,	0xE0,	

0xC0,	0x00,	0x00,	0x00	},
{	0x00,	0xFC,	0xFF,	0xFF,	0xFF,	0xFF,	0x07,	0x01,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x01,	0x07,	0xFF,	0xFF,	0xFF,	

0xFF,	0xFC,	0x00	},
{	0x00,	0x3F,	0xFF,	0xFF,	0xFF,	0xFF,	0xE0,	0x80,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	0xE0,	0xFF,	0xFF,	0xFF,	

0xFF,	0x3F,	0x00	},
{	0x00,	0x00,	0x00,	0x03,	0x07,	0x0F,	0x0F,	0x1F,	0x1F,	0x3F,	0x3E,	0x3E,	0x3E,	

0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3F,	0x1F,	0x1F,	0x0F,	0x0F,	0x07,	0x03,	

0x00,	0x00,	0x00	}};

const BYTE OFLetterKH[4][30] = {{	0x00,	0x00,	0x00,	0xC0,	0xE0,	0xF0,	0xF0,	0xF8,	0xF8,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xF8,	0xF8,	0xF0,	0xF0,	0xE0,	

0xC0,	0x00,	0x00,	0x00	},
{	0x00,	0xFC,	0xFF,	0xFF,	0xFF,	0xFF,	0x07,	0x01,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x01,	0x07,	0xFF,	0xFF,	0xFF,	

0xFF,	0xFC,	0x00	},
{	0x00,	0x3F,	0xFF,	0xFF,	0xFF,	0xFF,	0xE0,	0x80,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	0xE0,	0xFF,	0xFF,	0xFF,	

0xFF,	0x3F,	0x00	},
{	0x00,	0x00,	0x00,	0x03,	0x07,	0x0F,	0x0F,	0x1F,	0x1F,	0x3F,	0x3E,	0x3E,	0x3E,	

0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3F,	0x1F,	0x1F,	0x0F,	0x0F,	0x07,	0x03,	

0x00,	0x00,	0x00	}};

const BYTE OFLetterKV[4][30] = {{	0x00,	0xE0,	0xC0,	0x80,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	0xC0,	

0xE0,	0xF0,	0xF8,	0x00	},
{	0x00,	0x07,	0x0F,	0x1F,	0x3F,	0x7E,	0xFC,	0xF8,	0xF0,	0xE0,	0xC0,	0x80,	0x00,	

0x00,	0x00,	0x00,	0x80,	0xC0,	0xE0,	0xF0,	0xF8,	0xFC,	0x7E,	0x3F,	0x1F,	0x0F,	0x07,	

0x03,	0x01,	0x00	},
{	0x00,	0x80,	0x80,	0x80,	0x80,	0x80,	0x80,	0x81,	0x83,	0x87,	0x8F,	0x9F,	0xBF,	

0xFE,	0xFE,	0xFF,	0xFF,	0xEF,	0xC7,	0x83,	0x81,	0x80,	0x80,	0x80,	0x80,	0x80,	0x80,	

0x80,	0x80,	0x00	},
{	0x00,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	

0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	

0x07,	0x07,	0x00	}};

const BYTE OFLetterUH[4][30] = {{	0x00,	0xE0,	0xC0,	0x80,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	0xC0,	

0xE0,	0xF0,	0xF8,	0x00	},
{	0x00,	0x07,	0x0F,	0x1F,	0x3F,	0x7E,	0xFC,	0xF8,	0xF0,	0xE0,	0xC0,	0x80,	0x00,	

0x00,	0x00,	0x00,	0x80,	0xC0,	0xE0,	0xF0,	0xF8,	0xFC,	0x7E,	0x3F,	0x1F,	0x0F,	0x07,	

0x03,	0x01,	0x00	},
{	0x00,	0x80,	0x80,	0x80,	0x80,	0x80,	0x80,	0x81,	0x83,	0x87,	0x8F,	0x9F,	0xBF,	

0xFE,	0xFE,	0xFF,	0xFF,	0xEF,	0xC7,	0x83,	0x81,	0x80,	0x80,	0x80,	0x80,	0x80,	0x80,	

0x80,	0x80,	0x00	},
{	0x00,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	

0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	

0x07,	0x07,	0x00	}};

const BYTE OFLetterUV[4][30] = {{	0x00,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	

0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0xFC,	0xF8,	0xF8,	0xF0,	0xF0,	0xE0,	

0xC0,	0x00,	0x00,	0x00	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x01,	0x07,	0xFF,	0xFF,	0xFF,	

0xFF,	0xFC,	0x00	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	0xE0,	0xFF,	0xFF,	0xFF,	

0xFF,	0x3F,	0x00	},
{	0x00,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	

0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3F,	0x1F,	0x1F,	0x0F,	0x0F,	0x07,	0x03,	

0x00,	0x00,	0x00	}};

const BYTE OFLetterBH[4][30] = {{	0x00,	0x00,	0xFE,	0xFE,	0xFE,	0xFE,	0xFE,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	

0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x7E,	0xFC,	0xFC,	0xFC,	0xF8,	0xF0,	0xC0,	

0x00,	0x00,	0x00,	0x00	},
{	0x00,	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	

0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xF0,	0xF8,	0xFF,	0x7F,	0x7F,	0x3F,	0x0F,	0x00,	

0x00,	0x00,	0x00	},
{	0x00,	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	

0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	0x07,	0x0F,	0xFF,	0xFF,	0xFE,	0xFC,	0xF0,	

0x00,	0x00,	0x00	},
{	0x00,	0x00,	0x7F,	0x7F,	0x7F,	0x7F,	0x7F,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	

0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7E,	0x7F,	0x3F,	0x3F,	0x1F,	0x0F,	0x03,	

0x00,	0x00,	0x00	}};

const BYTE OFLetterBV[4][30] = {{	0x00,	0x00,	0xFE,	0xFE,	0xFE,	0xFE,	0xFE,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	

0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x3E,	0x7E,	0xFC,	0xFC,	0xFC,	0xF8,	0xF0,	0xC0,	

0x00,	0x00,	0x00,	0x00	},
{	0x00,	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	

0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xF0,	0xF8,	0xFF,	0x7F,	0x7F,	0x3F,	0x0F,	0x00,	

0x00,	0x00,	0x00	},
{	0x00,	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	

0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	0x07,	0x0F,	0xFF,	0xFF,	0xFE,	0xFC,	0xF0,	

0x00,	0x00,	0x00	},
{	0x00,	0x00,	0x7F,	0x7F,	0x7F,	0x7F,	0x7F,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	

0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7C,	0x7E,	0x7F,	0x3F,	0x3F,	0x1F,	0x0F,	0x03,	

0x00,	0x00,	0x00	}};

const BYTE OFLetterHH[4][30] = {{	0x00,	0x00,	0xFE,	0xFE,	0xFE,	0xFE,	0xFE,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xFE,	0xFE,	0xFE,	

0xFE,	0xFE,	0x00,	0x00	},
{	0x00,	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	

0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xFF,	0xFF,	0xFF,	0xFF,	

0xFF,	0x00,	0x00	},
{	0x00,	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	

0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	0xFF,	0xFF,	0xFF,	0xFF,	

0xFF,	0x00,	0x00	},
{	0x00,	0x00,	0x7F,	0x7F,	0x7F,	0x7F,	0x7F,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x7F,	0x7F,	0x7F,	0x7F,	

0x7F,	0x00,	0x00	}};

const BYTE OFLetterHV[4][30] = {{	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	

0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	

0xF8,	0xF8,	0xF8,	0xF8	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xFF,	

0xFF,	0xFF,	0xFF,	0xFF,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xFF,	

0xFF,	0xFF,	0xFF,	0xFF,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00	},
{	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	

0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	

0x1F,	0x1F,	0x1F	}};

const BYTE OFLetterNH[4][30] = {{	0x00,	0x00,	0xFE,	0xFE,	0xFE,	0xFE,	0xFE,	0xE0,	0xC0,	0x80,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xFE,	0xFE,	0xFE,	

0xFE,	0xFE,	0x00,	0x00	},
{	0x00,	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x0F,	0x1F,	0x3F,	0x7F,	0xFE,	0xFC,	

0xF8,	0xF0,	0xE0,	0xC0,	0x80,	0x00,	0x00,	0x00,	0x00,	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	

0xFF,	0x00,	0x00	},
{	0x00,	0x00,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x00,	0x00,	0x00,	0x00,	0x00,	0x01,	

0x03,	0x07,	0x0F,	0x1F,	0x3F,	0x7F,	0xFE,	0xFC,	0xF8,	0xF0,	0xFF,	0xFF,	0xFF,	0xFF,	

0xFF,	0x00,	0x00	},
{	0x00,	0x00,	0x7F,	0x7F,	0x7F,	0x7F,	0x7F,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x01,	0x03,	0x07,	0x7F,	0x7F,	0x7F,	0x7F,	

0x7F,	0x00,	0x00	}};

const BYTE OFLetterNV[4][30] = {{	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	

0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	0xF8,	

0xF8,	0xF8,	0xF8,	0xF8	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	

0xC0,	0xE0,	0xF0,	0xF8,	0xFC,	0xFE,	0x7F,	0x3F,	0x1F,	0x0F,	0x07,	0x03,	0x01,	0x00,	

0x00,	0x00,	0x00	},
{	0x00,	0x00,	0x00,	0x00,	0x80,	0xC0,	0xE0,	0xF0,	0xF8,	0xFC,	0xFE,	0x7F,	0x3F,	

0x1F,	0x0F,	0x07,	0x03,	0x01,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00	},
{	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	

0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	0x1F,	

0x1F,	0x1F,	0x1F	}};

const BYTE OFLetterYH[4][30] = {{	0x00,	0x00,	0x7E,	0xFE,	0xFC,	0xF8,	0xF0,	0xE0,	0xC0,	0x80,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	0xC0,	0xE0,	0xF0,	0xF8,	0xFC,	

0xFE,	0x7E,	0x00,	0x00	},
{	0x00,	0x00,	0x00,	0x00,	0x01,	0x03,	0x07,	0x0F,	0x1F,	0x3F,	0x7F,	0xFE,	0xFC,	

0xF8,	0xF0,	0xF0,	0xF8,	0xFC,	0xFE,	0x7F,	0x3F,	0x1F,	0x0F,	0x07,	0x03,	0x01,	0x00,	

0x00,	0x00,	0x00	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xFF,	

0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00	},
{	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x7F,	

0x7F,	0x7F,	0x7F,	0x7F,	0x7F,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00	}};

const BYTE OFLetterYV[4][30] = {{	0x18,	0x38,	0x78,	0xF8,	0xF8,	0xF8,	0xF0,	0xE0,	0xC0,	0x80,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00	},
{	0x00,	0x00,	0x00,	0x00,	0x01,	0x03,	0x07,	0x0F,	0x1F,	0x3F,	0x7F,	0xFE,	0xFC,	

0xF8,	0xF0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	

0xE0,	0xE0,	0xE0	},
{	0x00,	0x00,	0x00,	0x00,	0x80,	0xC0,	0xE0,	0xF0,	0xF8,	0xFC,	0xFE,	0x7F,	0x3F,	

0x1F,	0x0F,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	0x07,	

0x07,	0x07,	0x07	},
{	0x18,	0x1C,	0x1E,	0x1F,	0x1F,	0x1F,	0x0F,	0x07,	0x03,	0x01,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00	}};

const BYTE OFLetterSH[4][30] = {{	0x00,	0x00,	0x00,	0x80,	0xE0,	0xF0,	0xF8,	0xF8,	0x7C,	0x3C,	0x3C,	0x3C,	

0x3C,	0x3C,	0x3C,	0x3C,	0x3C,	0x3C,	0x3C,	0x3C,	0x7C,	0xF8,	0xF8,	0xF0,	0xE0,	0x80,	

0x00,	0x00,	0x00,	0x00	},
{	0x00,	0x00,	0x00,	0x1F,	0x7F,	0xFF,	0xFF,	0xF0,	0xE0,	0xC0,	0xC0,	0xC0,	0xC0,	

0xC0,	0xC0,	0xC0,	0xC0,	0xC0,	0xC0,	0xC0,	0xC0,	0x80,	0x83,	0x03,	0x03,	0x03,	0x00,	

0x00,	0x00,	0x00	},
{	0x00,	0x00,	0x00,	0xC0,	0xC0,	0xC0,	0xC1,	0x01,	0x03,	0x03,	0x03,	0x03,	0x03,	

0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	0x03,	0x07,	0x0F,	0xFF,	0xFF,	0xFE,	0xF8,	0x00,	

0x00,	0x00,	0x00	},
{	0x00,	0x00,	0x00,	0x01,	0x07,	0x0F,	0x1F,	0x1F,	0x3E,	0x3C,	0x3C,	0x3C,	0x3C,	

0x3C,	0x3C,	0x3C,	0x3C,	0x3C,	0x3C,	0x3C,	0x3E,	0x1F,	0x1F,	0x0F,	0x07,	0x01,	0x00,	

0x00,	0x00,	0x00	}};

const BYTE OFLetterSV[4][30] = {{	0x00,	0x00,	0x00,	0x80,	0xC0,	0xC0,	0xE0,	0xE0,	0xE0,	0x00,	0x00,	0x00,	

0x00,	0x00,	0x00,	0x80,	0xC0,	0xC0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xE0,	0xC0,	0xC0,	

0x80,	0x00,	0x00,	0x00	},
{	0x00,	0xFC,	0xFF,	0xFF,	0xFF,	0x07,	0x03,	0x01,	0x01,	0x00,	0x00,	0x00,	0x00,	

0xFC,	0xFF,	0xFF,	0xFF,	0x07,	0x03,	0x01,	0x01,	0x01,	0x01,	0x03,	0x07,	0xFF,	0xFF,	

0xFF,	0xFC,	0x00	},
{	0x00,	0x7F,	0xFF,	0xFF,	0xFF,	0xC0,	0x80,	0x00,	0x00,	0x00,	0x00,	0x80,	0xC0,	

0xFF,	0xFF,	0xFF,	0x7F,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x80,	0xC0,	0xFF,	0xFF,	

0xFF,	0x7F,	0x00	},
{	0x00,	0x00,	0x01,	0x03,	0x07,	0x07,	0x0F,	0x0F,	0x0F,	0x0F,	0x0F,	0x0F,	0x07,	

0x07,	0x03,	0x01,	0x00,	0x00,	0x00,	0x00,	0x00,	0x0F,	0x0F,	0x0F,	0x07,	0x07,	0x03,	

0x01,	0x00,	0x00	}};

/*const BYTE* OFGraphicsText[MAX_MODES][2][3][30] = {
{{OFLetterHH,OFLetterEH,OFLetterYH},{OFLetterHV,OFLetterEV,OFLetterYV}},
{{OFSignalNull,OFLetterOH,OFLetterKH},{OFSignalNull,OFLetterOV,OFLetterKV}},
{{OFLetterUH,OFLetterSH,OFLetterBH},{OFLetterUV,OFLetterSV,OFLetterBV}},
{{OFLetterCH,OFLetterOH,OFLetterNH},{OFLetterCV,OFLetterOV,OFLetterNV}},
{{OFLetterRH,OFLetterEH,OFLetterCH},{OFLetterRV,OFLetterEV,OFLetterCV}},
{{OFLetterEH,OFLetterRH,OFLetterRH},{OFLetterEV,OFLetterRV,OFLetterRV}},
};						 */

const BYTE* OFGraphicsSignal[2][6][30] = {	
{OFSignal0H,OFSignal0V},
{OFSignal1H,OFSignal1V},
{OFSignal2H,OFSignal2V},
{OFSignal3H,OFSignal3V},
{OFSignal4H,OFSignal4V},
{OFSignal5H,OFSignal5V},
};