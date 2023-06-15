#define CLK 13
#define DT  12
#define DONE 11
#define RQST 10

boolean clk = 0, envio = 0;
int valor = 0, i = 0;

void setup() {
  pinMode(DONE, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DT, OUTPUT);
  pinMode(RQST, INPUT);
  
  Serial.begin(9600);

}

void loop() {


    if(digitalRead(RQST))
    {
      envio = 1;
      digitalWrite(DONE, LOW);
      valor = analogRead(A0);       
    }
    if(envio == 1)
    {
      delay(10);
////////////Envia dados junto ao clock      
      if((clk == 0)&&(i<10))
      {
        if(bitRead(valor,i) == 0)
            digitalWrite(DT,LOW);
        else
            digitalWrite(DT,HIGH);
         i++;
      } 
////////////Envia clock     

      
      
      clk = !clk;   
      if(clk == 1)
        digitalWrite(CLK,HIGH);  
      else
        digitalWrite(CLK,LOW);

////////////Termina operação Envia DONE
      if(i > 9)
      {
        digitalWrite(DONE, HIGH);
        i = 0;
        envio = 0;
        clk = 0;  
      }      
  
    }
  
}
