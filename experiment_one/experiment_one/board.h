//???
#define F_CPU (16000000)
#define OSC_DIV (1)


// #     #    #    ######  ####### 
// #     #   # #   #     #    #    
// #     #  #   #  #     #    #    
// #     # #     # ######     #    
// #     # ####### #   #      #    
// #     # #     # #    #     #    
//  #####  #     # #     #    #   

#define UART0 _SFR_MEM8(0xC0)
#define UART1 _SFR_MEM8(0xC8)
#define UART2 _SFR_MEM8(0xD0)

#define UCSRA (0)
#define UCSRB (1)
#define UCSRC (2)
#define UCSRD (3)
#define UBRRL (4)
#define UBRRH (5)
#define UDR (6)

