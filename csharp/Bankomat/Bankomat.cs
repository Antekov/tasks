using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;

/**
Разработать эмулятор банковского терминал с выдачей и вносом денежных купюр. Система должна: 

Пользователь 

1. Знать пользователя по типу карточки, сумму денег на счету, уметь вносить и списывать со счета 
2. В банкомат загружены N купюр номиналом: 50, 100, 500, 1000, 2000 руб 
3. Банкомат должен выдавать денежные средства равномерно опустошая денежные слоты, 
   и не делая перекосов по нехватке какого-либо номинала (по возможности). 
4. Выдавать или отказывать в выдаче, при нехватке денежных купюр, списывая со счета и 
   уменьшая к-во денег в терминале 

5. Проверять пин код, отказывать в выдаче, предлагать сервисный набор функций 
6. Выводить отчет о последних 3 операциях по снятию и вносу наличности. 
7. Сообщать сколько и какого номинала ден .знаки остались в терминале 
8. Осуществлять перевод с карты на карту по её номеру. 

Админ 

1. Сообщать о наличии остатков купюр, по номиналам оставшихся на выдачу 
2. Сообщать о наличии остатков купюр, по номиналам загруженных пользователем 
3. Выводить статистику (средняя сумма снятия, средняя сумма загрузки, 
   максимальная/минимальная сумма снятия и загрузки, какой номинал вносили чаще/реже 
   других купюр) 

4. Уметь загружать новые купюры 

Общее 

1. Консольный интерфейс 
2. Вывод сообщений об ошибках 
3. Надежность 
4. Дополнительный функционал приветствуется, но не в ущерб основному 
*/

namespace Bankomat
{

    class Bankomat
    {
        Bank bank;
        Client client;
        Card card;
        SlotSet slotSet;

        public Bankomat(Bank bank)
        {
            this.bank = bank;
            slotSet = new SlotSet();
        }

        public void LoadCash(Dictionary<int, int> cash)
        {
            slotSet.Deposit(cash);
            slotSet.ResetCounts();
        }

        public void Start()
        {
            while (true)
            {
                Screen.Greetings(bank);

                string cardNumber = Screen.getCardNumber("Input card number:");

                client = bank.getClientByCard(cardNumber);
                card = bank.getCardByNumber(cardNumber);

                if (client != null)
                {
                    if (bank.isAdmin(client))
                    {
                        handleAdmin();
                    }
                    else
                    {
                        handleClient();
                    }
                }
                else {
                    Screen.ClientNotFound();
                }
            }
        }
        
       
        void handleAdmin() 
        {
            int m = 1;

            while (m > 0)
            {
                Screen.MainMenuAdmin(client);

                m = Screen.getMenuItem(5);
                switch (m)
                {
                    case 1:
                        Screen.ShowSlots(slotSet);
                        break;
                    case 2:
                        Screen.ShowClientSlots(slotSet);
                        break;
                    case 3:
                        Screen.ShowStatistic(getStatistic());
                        break;
                    case 4:
                        cashInSlots();
                        break;
                    case 5:
                        Screen.ShowTransactions(bank.getLastTransactions(100));
                        break;
                    default:
                        break;
                }
            }
        }
        Dictionary<string, string> getStatistic()
        {
            Dictionary<string, string> stat = new Dictionary<string, string>();

            stat["Average cash out"] = bank.getStatAvr(Transaction.Type.CashOut).ToString();
            stat["Average cash in "] = bank.getStatAvr(Transaction.Type.CashIn).ToString();
            stat["Min/Max cash out"] = bank.getStatMin(Transaction.Type.CashOut).ToString() + " / " + bank.getStatMax(Transaction.Type.CashOut).ToString();
            stat["Min/Max cash in "] = bank.getStatMin(Transaction.Type.CashIn).ToString() + " / " + bank.getStatMax(Transaction.Type.CashIn).ToString();
            stat["Popular/unpopular cash in"] = slotSet.getPopularCash(Transaction.Type.CashIn).ToString() + " / " + slotSet.getUnpopularCash(Transaction.Type.CashIn).ToString();

            return stat;
        }

        

        void handleClient() {
            int m = 1;

            while (m > 0)
            {
                Screen.MainMenuClient(client);

                m = Screen.getMenuItem(5);
                switch (m)
                {
                    case 1:
                        Screen.ShowBalance(client);
                        break;
                    case 2:
                        cashIn();
                        break;
                    case 3:
                        cashOut();
                        break;
                    case 4:
                        moveToCard();
                        break;
                    case 5:
                        Screen.ShowTransactions(client.getLastTransactions(3));
                        break;
                    default:
                        break;
                }
            }
        }

        private void cashOut()
        {
            int amount = Screen.getAmount(client.Amount);

            if (amount % (int) SlotSet.nominals[0] > 0) {
                Screen.CashNotValid();
                return;
            }

            string pin = Screen.getPin();

            if (card.isValidPin(pin))
            {
                if (slotSet.Withdraw(amount))
                {
                    client.actionCashOut(card, amount);
                }
                else 
                {
                    Screen.CashNotEnough();
                }
            }
            else
            {
                Screen.WrongPin();
            }
        }

        void moveToCard()
        {
            Console.Clear();
            string cardNumber = Screen.getCardNumber("Input card number to move:");

            Client otherClient = bank.getClientByCard(cardNumber);
            Card otherCard = bank.getCardByNumber(cardNumber);

            if (otherClient != null)
            {
                Screen.MoveAmount(client, otherClient);
                int amount = Screen.getAmount(client.Amount);

                string pin = Screen.getPin();

                if (card.isValidPin(pin))
                {
                    client.actionMove(card, otherCard, amount);
                } 
                else
                {
                    Screen.WrongPin();
                }
            }
            else
            {
                Screen.WrongCard();
            }
        }

        int cashToAmount(Dictionary<int, int> cash)
        {
            int amount = 0; 
            foreach (var c in cash)
            {
                amount += c.Key * c.Value;
            }
            return amount;
        }

        Dictionary<int, int> getCashFromClient()
        {
            Dictionary<int, int> cash = new Dictionary<int, int>();
            int amount = 0;

            while (true)
            {
                Screen.CashInTitle(amount);

                int m = Screen.getCashAmount();

                if (m == 0) break;

                if (m < 0) { continue; }

                if (cash.ContainsKey(m))
                {
                   cash[m] += 1;
                }
                else
                {
                    cash.Add(m, 1);
                }
                amount += m;
            }

            return cash;
        }

        void cashIn() {
            Dictionary<int, int> cash = getCashFromClient();
            
            int amount = cashToAmount(cash);

            Screen.CashInConfirmMenu(amount);

            int m = Screen.getMenuItem(2, 1);

            if (m == 1)
            {
                slotSet.Deposit(cash);
                client.actionCashIn(card, amount);
            }
        }

        void cashInSlots()
        {
            Dictionary<int, int> cash = getCashFromClient();

            int amount = cashToAmount(cash);

            Screen.CashInConfirmMenu(amount);

            int m = Screen.getMenuItem(2, 1);

            if (m == 1)
            {
                slotSet.Deposit(cash);
            }
        }
    }
}
