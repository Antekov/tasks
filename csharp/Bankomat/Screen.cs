using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace Bankomat
{
    class Screen
    {
        public static void Greetings(Bank bank = null)
        {
            Console.Clear();
            Console.WriteLine(bank.Name);
            Console.WriteLine("============================");
            Console.WriteLine("Welcome!");
        }

        public static void MainMenuClient(Client client)
        {
            Console.Clear();
            Console.WriteLine("Welcome, {0}!", client.Name);
            Console.WriteLine("Select operation:");
            Console.WriteLine("1. Display balance");
            Console.WriteLine("2. Deposit cash");
            Console.WriteLine("3. Withdraw cash");
            Console.WriteLine("4. Move to other card");
            Console.WriteLine("5. Display transactions");
            Console.WriteLine("----------------");
            Console.WriteLine("0. Exit");
        }

        internal static void MainMenuAdmin(Client client)
        {
            Console.Clear();
            Console.WriteLine("Admin mode");
            Console.WriteLine("Welcome, {0}!", client.Name);
            Console.WriteLine("Select operation:");
            Console.WriteLine("1. Display cash slots");
            Console.WriteLine("2. Display cash in slots");
            Console.WriteLine("3. Display statistic");
            Console.WriteLine("4. Cash in slots");
            Console.WriteLine("5. Display transactions");
            Console.WriteLine("----------------");
            Console.WriteLine("0. Exit");
        }

        static void Pause()
        {
            Console.Write("Press <any> key to return");
            Console.ReadKey();
        }

        internal static void ClientNotFound()
        {
            Console.WriteLine("Card number not found in clients database.");
            Pause();
        }

        internal static void CashNotValid()
        {
            Console.WriteLine("Amount can't be cash out.");
            Pause();
        }

        internal static void CashNotEnough()
        {
            Console.WriteLine("Amount can't be cash out. Not enough cash in ATM.");
            Pause();
        }

        public static void WrongCard()
        {
            Console.WriteLine("Card number not found in clients database.");
            Pause();
        }

        internal static void WrongMenuItem(int maxItem, int minItem = 0)
        {
            Console.WriteLine($"Wrong menu item. Expected value from [{minItem}..{maxItem}]");
            Pause();
        }

        internal static void WrongAmount(int maxAmount, int minAmount = 100)
        {
            Console.WriteLine($"Wrong amount. Expected value from [{minAmount}..{maxAmount}]");
            Pause();
        }

        internal static void WrongCash()
        {
            Console.WriteLine("Wrong cash");
            Pause();
        }

        internal static void WrongPinFormat()
        {
            Console.WriteLine("Wrong pin format. Expected 4 digits");
            Pause();
        }

        

        internal static void WrongPin()
        {
            Console.WriteLine("Wrong PIN.");
            Pause();
        }

        internal static void ShowStatistic(Dictionary<string, string> stat)
        {
            Console.Clear();
            Console.WriteLine("Statistic:");
            foreach (var s in stat)
            {
                Console.WriteLine($"{s.Key,25}: {s.Value}");
            }
            Pause();
        }

        internal static void CashOutTitle()
        {
            Console.Clear();
            Console.WriteLine("Input amount to cash out:");
        }
        
        internal static void MoveAmount(Client client, Client otherClient)
        {
            Console.WriteLine("Move to {0}", otherClient.Name);
            Console.WriteLine("Your balance is: {0}", client.Amount);
            Console.WriteLine("Input amount to move:");
        }

        internal static void CashInTitle(int amount) 
        { 
            Console.Clear();
            Console.WriteLine("Insert cash into ATM. For submit insert 0");
            Console.WriteLine("Inserted: {0}", amount);
        }

        internal static void CashInConfirmMenu(int amount)
        {
            Console.Clear();
            Console.WriteLine("Select operation:");
            Console.WriteLine("1. Deposit {0}", amount);
            Console.WriteLine("2. Cancel");
        }
            

        internal static void ShowBalance(Client client)
        {
            Console.Clear();
            Console.WriteLine("Balance:");
            Console.WriteLine(client.Amount);
            Pause();
        }

        internal static void ShowTransactions(ArrayList transactions)
        {
            Console.Clear();
            if (transactions.Count > 0)
            {
                Console.WriteLine($"Last {transactions.Count} transactions:");
                foreach (Transaction t in transactions)
                {
                    Console.WriteLine(t.Description);
                }
            }
            else 
            {
                Console.WriteLine("No transactions");
            }
            Pause();
        }

        internal static void ShowSlots(SlotSet slotSet)
        {
            Console.Clear();
            Console.WriteLine("Cash Slots:");

            foreach (int nominal in SlotSet.nominals)
            {
                Console.WriteLine($"{nominal, 5}: {slotSet.Slots[nominal].Count, 4} pts.");
            }
            Pause();
        }

        internal static void ShowClientSlots(SlotSet slotSet)
        {
            Console.Clear();
            Console.WriteLine("Cash which added by clients in slots:");

            foreach (int nominal in SlotSet.nominals)
            {
                Console.WriteLine($"{nominal,5}: {slotSet.Slots[nominal].CountIn,4} pts.");
            }
            Pause();
        }

        internal static int getMenuItem(int maxItem, int minItem = 0) {
            while (true)
            {
                try
                {
                    int res = int.Parse(Console.ReadLine());
                    if (res > maxItem || res < minItem)
                    {
                        throw new Exception();
                    }
                    return res;
                }
                catch (Exception)
                {
                    Screen.WrongMenuItem(maxItem, minItem);
                }
            }
        }

        internal static int getCashAmount()
        {
            while (true)
            {
                try
                {
                    int res = int.Parse(Console.ReadLine());

                    if (res == 0) return res;

                    if (!SlotSet.nominals.Contains(res))
                    {
                        throw new Exception();
                    }
                    return res;
                }
                catch (Exception)
                {
                    Screen.WrongCash();
                    return -1;
                }
            }
        }
        
        internal static int getAmount(int maxAmount, int minAmount = 50)
        {
            while (true)
            {
                try
                {
                    Screen.CashOutTitle();

                    int res = int.Parse(Console.ReadLine());
                    if (res > maxAmount || res < minAmount)
                    {
                        throw new Exception();
                    }
                    return res;
                }
                catch (Exception)
                {
                    Screen.WrongAmount(maxAmount, minAmount);
                }
            }
        }
        internal static string getPin()
        {
            while (true)
            {
                try
                {
                    Console.Clear();
                    Console.WriteLine("Input PIN: ");

                    string s = Console.ReadLine();

                    if (s.Length > 4) { throw new Exception(); }

                    int res = int.Parse(s);
                    
                    return s;
                }
                catch (Exception)
                {
                    Screen.WrongPinFormat();
                }
            }
        }

        internal static string getCardNumber(string message = "Input card number:")
        {
            Console.WriteLine(message);
            string res = Console.ReadLine();

            // if (res.Length > 5 || res.Length > 20) { throw new Exception(); }

            return res;
        }
    }
}
