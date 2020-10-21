using Microsoft.VisualBasic;
using System;
using System.Collections.Generic;
using System.Text;

namespace Bankomat
{
    class Card
    {
        public enum Type { Debit, Credit };
        public Type CardType { get; }
        public string Number { get; }
        private string Pin { get; }
        public DateTime Expiration { get; }

        public Client Client { get; }
        
        public Card(Card.Type cardType, string number, string pin, Client client)
        {
            CardType = cardType;
            Number = number;
            Pin = pin;
            Client = client;
            Expiration = new DateTime(DateTime.Now.Year + 4, DateTime.Now.Month, DateTime.Now.Day);
        }

        public bool isValidPin(string pin)
        {
            return pin.Equals(Pin);
        }
    }
}
