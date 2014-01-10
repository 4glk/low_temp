#if defined(__AVR_ATtiny13__)
#define __CPU	AVR_ATtiny13


#elif defined (__AVR_ATmega8__)
#define __CPU	AVR_ATmega8

#warning "all right its m8"
//#error "works !!!"

#elif defined (__AVR_ATmega32__)
#define __CPU	AVR_ATmega32


#elif defined (__AVR_ATtiny85__)
#define __CPU	AVR_ATtiny85


#else
#error "Your AVR is not supported (or at least not tested)"
#endif

