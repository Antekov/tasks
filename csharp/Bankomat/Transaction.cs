using System;
using System.Collections.Generic;
using System.Text;

namespace Bankomat
{
    class Transaction
    {
        public enum Type { CashIn, CashOut, Deposit, Withdraw }

        public static string TypeToStr(Type type)
        {
            string text = "";
            switch (type)
            {
                case Type.CashIn: 
                    text = "CashIn";
                    break;
                case Type.CashOut:
                    text = "CashOut";
                    break;
                case Type.Deposit:
                    text = "Deposit";
                    break;
                case Type.Withdraw:
                    text = "Withdraw";
                    break;
            }
            return text;
        }
        public Type TransactionType { get; }
        public DateTime Date { get; }

        public int Amount { get; }

        public Card Card { get; }
        public Card OtherCard { get; }

        public string Description { 
            get {
                string text = $"{Date} - {TypeToStr(TransactionType), 7}: {Amount, 8} RUB | Card # {Card.Number, 10}";
                if (OtherCard != null)
                {
                    text += $" | Other Card # {OtherCard.Number,10}";
                }
                return text;
            } 
        }

        public Transaction(Transaction.Type transactionType, Card card, int amount, Card otherCard=null)
        {
            TransactionType = transactionType;
            Date = DateTime.Now;
            Amount = amount;
            Card = card;
            OtherCard = otherCard;
        }
    }
}
