#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
//definitions for the wire connections
#define rs PC0
#define rw PC1
#define en PC2
#define data PORTD
#define keypad PORTB
//functions necessary
void lcd_init(); //to initialize lcd
void lcd_cmd(char cmd_out); //to send command to lcd
void lcd_data(char data_out); //to send data to lcd
void lcd_str(char *str); //to send string,, basically stripping each
// Check keypad entries by column and player
void check_colp11();
void check_colp12();
void check_colp13();
void check_colp14();
void check_colp21();
void check_colp22();
void check_colp23();
void check_colp24();
void player1_check(int,int);
void player2_check(int,int);
void winner_check();
int winnerplayer1 ;
int winnerplayer2 ;
int player1[4][4];
int player2[4][4];
int playerturn = 0;
int player1turn = 1;
int player2turn = 0;
int row1,row2,col1,col2;
int draw;
int ccp11,ccp12,ccp13,ccp14,ccp21,ccp22,ccp23,ccp24;
void setup() {
  // put your setup code here, to run once:
//set DDR
	DDRC |= (1 << rs) | (1 << rw) | (1 << en); //RS, RW, EN as outputs
	DDRD = 0xFF; //PORTB as outputs
	DDRB = 0x0F; //Set all 4 keypad rows as outputs and 4 keypad columns as inputs
	keypad = 0xFF; //Set keypad row values a 1 and turn on pull-ups for keypad columns
	lcd_init(); // Turn on display, turn on cursor, set cursor locatoin
	lcd_str("Connect four "); // Print to LCD screen
	_delay_ms(1000);
	lcd_cmd(0x02); // Return cursor home
	lcd_str("Penolio & Chikato");
	lcd_cmd(0xC0); // Set cursor at start of 1st column 2nd row
	lcd_str("CPE 301:final");
	_delay_ms(1000);
	lcd_cmd(0x01); // Clear display
}

void loop() {
  // put your main code here, to run repeatedly:
 if(playerturn == 0){ // resets for new game
   for(int i = 0; i < 4; i++){

     for(int j = 0; j < 4; j++){
       player1[i][j] = 0;
       player2[i][j] = 0;
     }
   }
	
   playerturn = 1;
     winnerplayer1 = 0 ;
     winnerplayer2 = 0 ;
	draw = 0;
	 lcd_str("NEW GAME!");
	 _delay_ms(1000);
	lcd_cmd(0x01); // Clear display
    ccp11=ccp12=ccp13=ccp14=ccp21=ccp22=ccp23=ccp24 = 3 ;

 }
    while(player1turn == 1){// player1 turn
    check_colp11();
		lcd_cmd(0xC0); // Reset cursor at start of line
		check_colp12();
		lcd_cmd(0xC0);
		check_colp13();
		lcd_cmd(0xC0);
		check_colp14();
		lcd_cmd(0xC0);

    winner_check(); // checks for winner
    }
    if(winnerplayer1 == 1){// player 1 wins
      lcd_str("PlAYER1 WINS!");
	   _delay_ms(1000);
	    lcd_cmd(0x01); // Clear display
      playerturn = 0;
      player2turn = 0;
      player1turn = 1;
    }
    while(player2turn == 1){// player 2 turn
    check_colp21();
		lcd_cmd(0xC0); // Reset cursor at start of line
		check_colp22();
		lcd_cmd(0xC0);
		check_colp23();
		lcd_cmd(0xC0);
		check_colp24();
		lcd_cmd(0xC0);
    //playerturn++;
    //win_p2();
     winner_check();
    }
    if(winnerplayer2 == 1){// player 2 wins
      lcd_str("PlAYER2 WINS!");
	   _delay_ms(1000);
	    lcd_cmd(0x01); // Clear display
      playerturn = 0;
      player2turn = 0;
      player1turn = 1;
    }
	else if(draw == 1){ // draw condition
		lcd_str("PlAYERS DRAW");
	   _delay_ms(1000);
	    lcd_cmd(0x01); // Clear display
      playerturn = 0;
      player2turn = 0;
      player1turn = 1;
	  
		
	}


}
void winner_check()// this function checks for win conditions and draw conditions for both players
{
  int zero, one,two,three,four,five,six,seven,eight,nine;
  int  a,b,c,d,e,f,g,h,k,l;
  zero=one=two=three=four=five=six=seven=eight=nine=a=b=c=d=e=f=g=h=k=l=0;


  
// below checks for draw by seeing if all spots are taken
int count = 0;
for(int i = 0; i < 4; i++){

     for(int j = 0; j < 4; j++){
      if( player1[i][j] == 1){
		  count++;
	  }
      else if( player2[i][j] == 1){
		  count++;
	  }
     }
   }
// below checks for win conditions if any are 0 for a win condition that condition is not met
zero =player1[0][0]*player1[1][0]*player1[2][0]*player1[3][0];
one = player1[0][1]*player1[1][1]*player1[2][1]*player1[3][1];
two =player1[0][2]*player1[1][2]*player1[2][2]*player1[3][2];
three = player1[0][3]*player1[1][3]*player1[2][3]*player1[3][3];
four = player1[0][1]*player1[0][2]*player1[0][2]*player1[0][3];
five = player1[1][1]*player1[1][2]*player1[1][2]*player1[1][3];
six = player1[2][1]*player1[2][2]*player1[2][2]*player1[2][3];
seven = player1[3][1]*player1[3][2]*player1[3][2]*player1[3][3];
eight = player1[0][0]*player1[1][1]*player1[2][2]*player1[3][3];
nine = player1[0][3]*player1[1][2]*player1[2][1]*player1[3][0];
if(zero|one|two|three|four|five|six|seven|eight|nine){ // checks for any win condition 
  winnerplayer1 = 1;
}
a =player2[0][0]*player2[1][0]*player2[2][0]*player2[3][0];
b = player2[0][1]*player2[1][1]*player2[2][1]*player2[3][1];
c =player2[0][2]*player2[1][2]*player2[2][2]*player2[3][2];
d = player2[0][3]*player2[1][3]*player2[2][3]*player2[3][3];
e = player2[0][1]*player2[0][2]*player2[0][2]*player2[0][3];
f = player2[1][1]*player2[1][2]*player2[1][2]*player2[1][3];
g = player2[2][1]*player2[2][2]*player2[2][2]*player2[2][3];
h = player2[3][1]*player2[3][2]*player2[3][2]*player2[3][3];
k = player2[0][0]*player2[1][1]*player2[2][2]*player2[3][3];
l = player2[0][3]*player2[1][2]*player2[2][1]*player2[3][0];
if(a|b|c|d|e|f|g|h|k|l){
  winnerplayer2 = 1;
}
if(count == 16){ // checks for the draw 
	draw = 1;
}

}
void lcd_init()// given lcd stuff from the lab for the next few functions
{
	PORTC &= ~(1 << en);
	_delay_ms(100); //Wait >40ms after power is applied
	lcd_cmd(0x30); //CMD: Wake Up
	_delay_ms(30);
	lcd_cmd(0x30); //CMD: Wake Up #2
	_delay_ms(10);
	lcd_cmd(0x30); //CMD: Wake Up #3
	_delay_ms(10);
	// Initializing to 2 lines & 5x8 font
	lcd_cmd(0x38);
	_delay_ms(10);
	// Display on, cursor on
	lcd_cmd(0x0E);
	_delay_ms(10);
	// Clear LCD
	lcd_cmd(0x01);
	_delay_ms(10);
	// Set cursor position to top row 0x80
	lcd_cmd(0x80);
	_delay_ms(10);
}
void lcd_cmd(char cmd_out)
{
	//send the cmd_out to data
	data = cmd_out;
	//set rs = 0 ,rw=0 and en =1
	PORTC &= ~(1 << rs) & ~(1 << rw);
	PORTC |= (1 << en);
	//wait for small delay 10ms
	_delay_ms(10);
	//set rs = 0 ,rw=0 and en =0
	//PORTC &= ~(1 << rs) & ~(1 << rw);
	PORTC &= ~(1 << en);
	//wait for small delay 10ms
	_delay_ms(10);
}
void lcd_data(char data_out)
{
	//send the data_out to data
	data = data_out;
	//set rs = ? ,rw=? and en =?
	PORTC &= ~(1 << rw);
	PORTC |= (1 << rs) | (1 << en);
	//wait for small delay 10ms
	_delay_ms(10);
	//set rs = ? ,rw=? and en =?
	PORTC &= ~(1 << en);
	//wait for small delay 10ms
	_delay_ms(10);
}
void lcd_str(char *str)
{
	unsigned int i=0;
	while(str[i]!='\0')
	{
		lcd_data(str[i]);
		i++;
	}
}
void player1_check(int row,int col)// checks if a postion is open for the player or taken already
{
  if(player2[row][col] == 0 ){
    player1[row][col] = 1; // connect 4 logic
		if(col == 0){
			ccp11--;
		}
		else if(col == 1){
			ccp12--;
		}
		else if(col == 2){
			ccp13--;
		}
		else if(col == 3){
			ccp14--;
		}
  }
  else{
    player1[row][col] = 0;
    lcd_str("# taken!!!!!!!"); // Print to LCD screen
	_delay_ms(1000);
 	lcd_cmd(0x01); // Clear display
  }
}
void player2_check(int row,int col)// checks if a postion is open for the player or taken already
{
  if(player1[row][col] == 0 ){
    player2[row][col] = 1;
		if(col == 0){
			ccp11--;
		}
		else if(col == 1){
			ccp12--;
		}
		else if(col == 2){
			ccp13--;
		}
		else if(col == 3){
			ccp14--;
		} 

 }
  else{
    player2[row][col] = 0;
    lcd_str("# taken!!!!!!!"); // Print to LCD screen
	_delay_ms(1000);
 	lcd_cmd(0x01); // Clear display
  }
}
// the rest of these functions just checks for the specific row and column press for each player
void check_colp11()
{
  
	uint16_t mask = 0b11110001;
	keypad = mask; // Column
	_delay_ms(10); // Wait for I/O state to change
	// For each keypad press in target column, check which row was pressed
	if((PINB & mask) == 0b00010001){player1_check(ccp11,0);player1turn = 0; player2turn = 1; lcd_str("p1 pressed 01");}

} 
void check_colp21()
{
    	uint16_t mask = 0b11110001;
	keypad = mask; // Column
	_delay_ms(10); // Wait for I/O state to change
	// For each keypad press in target column, check which row was pressed
	if((PINB & mask) == 0b00010001) {player2_check(ccp11,0);player2turn = 0; player1turn = 1;lcd_str("p2 pressed 01");}

  
}
void check_colp12()
{
  
	uint16_t mask = 0b11110010;
	keypad = mask; // Column
	_delay_ms(10); // Wait for I/O state to change
	// For each keypad press in target column, check which row was pressed
	if((PINB & mask) == 0b00010010) {player1_check(ccp12,1);player1turn = 0; player2turn = 1;lcd_str("p1 pressed 02");}

  }
void check_colp22()
{
    	uint16_t mask = 0b11110010;
	keypad = mask; // Column
	_delay_ms(10); // Wait for I/O state to change
	// For each keypad press in target column, check which row was pressed
	if((PINB & mask) == 0b00010010) {player2_check(ccp12,1);player2turn = 0; player1turn = 1;lcd_str("p2 pressed 02");}

}

void check_colp13()
{
	
  uint16_t mask = 0b11110100;
	keypad = mask; // Column
	_delay_ms(10); // Wait for I/O state to change
	// For each keypad press in target column, check which row was pressed
	if((PINB & mask) == 0b00010100) {player1_check(ccp13,2);player1turn = 0; player2turn = 1;lcd_str("p1 pressed 03");}

  }
void check_colp23()
{
      uint16_t mask = 0b11110100;
	keypad = mask; // Column
	_delay_ms(10); // Wait for I/O state to change
	// For each keypad press in target column, check which row was pressed
	if((PINB & mask) == 0b00010100) {player2_check(ccp13,2);player2turn = 0; player1turn = 1;lcd_str("p2 pressed 03");}

  
}
void check_colp14()
{

	uint16_t mask = 0b11111000;
	keypad = mask; // Column
	_delay_ms(10); // Wait for I/O state to change
	// For each keypad press in target column, check which row was pressed
	if((PINB & mask) == 0b00011000) {player1_check(ccp14,3);player1turn = 0; player2turn = 1;lcd_str("p1 pressed 04 ");}

}
void check_colp24()
 {
    	uint16_t mask = 0b11111000;
	keypad = mask; // Column
	_delay_ms(10); // Wait for I/O state to change
	// For each keypad press in target column, check which row was pressed
	if((PINB & mask) == 0b00011000) {player2_check(ccp14,3);player2turn = 0; player1turn = 1;lcd_str("p2 pressed 04 ");}

  
}
