void Sim900power(){
  PORTH|=1<<6;//digitalWrite(9, HIGH);
  delay(1000);
  PORTH&=~(1<<6);//digitalWrite(9, LOW);
  delay(5000);
}
