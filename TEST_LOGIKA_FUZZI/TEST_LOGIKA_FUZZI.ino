int a,b,c,d,mf1,x;

void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  a = -100;
  b = -50;
  c = 0;
  d = 5;
  mf1 = max(min(min((x-a)/(b-a), (d-x)/(d-c)),1),0);
}
