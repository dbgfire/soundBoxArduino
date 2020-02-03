#include <SD.h>
#include <SPI.h>
#include <arduino.h>
#include <MusicPlayer.h>
#include <MsTimer2.h>

// import method for shield
void midiSendByte(byte data)
{
  SPI.transfer(0x00);
  SPI.transfer(data);
}

void midiWriteData(byte cmd, byte high, byte low)
{
  while (!digitalRead(VS_DREQ));
  digitalWrite(VS_XDCS, LOW);
  midiSendByte(cmd);
  if ((cmd & 0xF0) <= 0xB0 || (cmd & 0xF0) >= 0xE0)
  {
    midiSendByte(high);
    midiSendByte(low);
  }
  else
  {
    midiSendByte(high);
  }
  digitalWrite(VS_XDCS, HIGH);
}
void midiNoteOn(byte channel, byte note, byte rate)
{
  midiWriteData((0x90 | channel), note, rate);
}

void midiNoteOff(byte channel, byte note, byte rate)
{
  midiWriteData((0x80 | channel), note, rate);
}
