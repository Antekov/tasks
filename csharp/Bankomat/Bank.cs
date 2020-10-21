
using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;

namespace Bankomat
{
    class Bank
    {
        public string Name { get; }

        ArrayList clients;
        ArrayList admins;

        Dictionary<string, Card> cards;

        public ArrayList Transactions;

        public Bank(string name = "Bank of America")
        {
            Name = name;
            clients = new ArrayList();
            admins = new ArrayList();

            cards = new Dictionary<string, Card>();
            Transactions = new ArrayList();
        }

        string generateCardNumber(Card.Type cardType = Card.Type.Debit)
        {
            return ((cardType == Card.Type.Debit ? 10000 : 20000) + cards.Count).ToString();
        }

        string generatePin()
        {
            return "0000";
        }

        internal void addTransaction(Transaction transaction)
        {
            Transactions.Add(transaction);
        }

        public void emitCard(Client client, Card.Type cardType)
        {
            Card card = new Card(cardType, generateCardNumber(), generatePin(), client);
            cards.Add(card.Number, card);
            client.addCard(card);
        }

        internal Client getClientByCard(string cardNumber)
        {
            if (cards.ContainsKey(cardNumber))
            {
                 return cards[cardNumber].Client;
            }
            return null;
        }

        internal Card getCardByNumber(string cardNumber)
        {
            if (cards.ContainsKey(cardNumber))
            {
                return cards[cardNumber];
            }
            return null;
        }

        public void addClient(Client client)
        {
            client.bank = this;
            clients.Add(client);
        }

        public void addAdmin(Client client)
        {
            client.bank = this;
            admins.Add(client);
            clients.Add(client);
        }

        public bool isAdmin(Client client)
        {
            return admins.Contains(client);
        }


        internal ArrayList getLastTransactions(int n = 100)
        {
            ArrayList transactions = new ArrayList();

            for (int i = Transactions.Count - 1; i >= 0 && n > 0; i--)
            {
                Transaction t = (Transaction)Transactions[i];
                if (t.TransactionType == Transaction.Type.CashIn || t.TransactionType == Transaction.Type.CashOut)
                {
                    transactions.Add(t);
                    n--;
                }
            }
            return transactions;
        }

        internal int getStatMax(Transaction.Type transactionType)
        {
            int res = 0;

            foreach (Transaction t in Transactions)
            {
                if (t.TransactionType == transactionType && t.Amount > res) res = t.Amount;
            }

            return res;
        }

        internal int getStatMin(Transaction.Type transactionType)
        {
            int res = 0;

            foreach (Transaction t in Transactions)
            {
                if (t.TransactionType == transactionType && (t.Amount < res || res == 0)) res = t.Amount;
            }

            return res;
        }

        internal double getStatAvr(Transaction.Type transactionType)
        {
            double res = 0;

            int sum = 0;
            int count = 0;

            foreach (Transaction t in Transactions)
            {
                if (t.TransactionType == transactionType)
                {
                    sum += t.Amount;
                    count += 1;
                }
            }

            if (count > 0) res = sum / count;

            return res;
        }
    }
}
