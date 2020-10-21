using System;
using System.Collections;
using System.Collections.Generic;

namespace Bankomat
{
    class Client
    {
        private int amount;
        public Dictionary<string, Card> Cards { get; }
        public string Name { get; set; }
        public int Amount { get { return amount; } }

        public Bank bank { get; set; }

        private ArrayList Transactions;

        public Client(string name, int amount)
        {
            Name = name;
            this.amount = amount;
            Cards = new Dictionary<string, Card>();
            Transactions = new ArrayList();
        }

        void registerTransaction(Transaction transaction)
        {
            Transactions.Add(transaction);
            bank.addTransaction(transaction);
        }

        public void addCard(Card card)
        {
            Cards[card.Number] = card;
        }

        public void actionCashIn(Card card, int amount)
        {
            this.amount += amount;
            Transaction transaction = new Transaction(Transaction.Type.CashIn, card, amount);
            registerTransaction(transaction);
        }

        public void actionCashOut(Card card, int amount)
        {
            this.amount -= amount;
            Transaction transaction = new Transaction(Transaction.Type.CashOut, card, amount);
            registerTransaction(transaction);
        }

        public void actionMove(Card card, Card otherCard, int amount)
        {
            this.amount -= amount;
            bank.getClientByCard(otherCard.Number).actionRecieve(otherCard, card, amount);
            Transaction transaction = new Transaction(Transaction.Type.Withdraw, card, amount, otherCard);
            registerTransaction(transaction);
        }

        public void actionRecieve(Card card, Card otherCard, int amount)
        {
            this.amount += amount;
            Transaction transaction = new Transaction(Transaction.Type.Deposit, card, amount, otherCard);
            registerTransaction(transaction);
        }

        internal ArrayList getLastTransactions(int n = 3)
        {
            ArrayList transactions = new ArrayList();

            for (int i = Transactions.Count - 1; i >= 0 && n > 0; i--) 
            {
                Transaction t = (Transaction) Transactions[i];
                if (t.TransactionType == Transaction.Type.CashIn || t.TransactionType == Transaction.Type.CashOut)
                {
                    transactions.Add(t);
                    n--;
                }
            }
            return transactions;
        }
    }
}
