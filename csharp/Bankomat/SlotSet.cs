using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;

namespace Bankomat
{
    class SlotSet
    {
        public static ArrayList nominals = new ArrayList(){50, 100, 200, 500, 1000, 2000};

        Dictionary<int, Slot> slots;
        public SlotSet()
        {
            slots = new Dictionary<int, Slot>();
            foreach (int nominal in nominals) {
                slots.Add(nominal, new Slot(nominal, 0, 100));
            }
        }

        public void Deposit(Dictionary<int, int> cash) 
        {
            foreach (var c in cash) {
                slots[c.Key].Deposit(c.Value);
            }
        }

        public Dictionary<int, int> GetCash(int amount)
        {
            Dictionary<int, int> cash = new Dictionary<int, int>();

            int i = nominals.Count - 1;
            while (amount > 0 && i >= 0)
            {
                int nominal = (int)nominals[i];
                if (amount >= nominal)
                {
                    cash[nominal] = amount / nominal;
                    amount -= (amount / nominal) * nominal;
                }
                i--;
            }

            if (amount == 0)
            {
                return cash;
            } else
            {
                return null;
            }
        }

        public bool CanWithdraw(Dictionary<int, int> cash)
        {
            foreach (var c in cash)
            {
                if (!slots[c.Key].CanWithdraw(c.Value))
                {
                    return false;
                }
            }
            return true;
        }

        public bool Withdraw(int amount) 
        {
            Dictionary<int, int> cash = GetCash(amount);

            if (CanWithdraw(cash))
            {
                foreach (var c in cash)
                {
                    slots[c.Key].Withdraw(c.Value);
                }
                return true;
            }
            return false;
        }

        internal void ResetCounts()
        {
            foreach (var slot in slots)
            {
                slot.Value.ResetCounts();
            }
        }

        internal Dictionary<int, Slot> Slots
        {
            get
            {
                return slots;
            }
        }

        internal int getPopularCash(Transaction.Type transactionType)
        {
            int res = 0;
            int maxCount = 0;

            foreach (var slot in Slots) 
            {
                if (transactionType == Transaction.Type.CashIn && slot.Value.CountIn > maxCount) { 
                    maxCount = slot.Value.CountIn;
                    res = slot.Key;
                }

                if (transactionType == Transaction.Type.CashOut && slot.Value.CountOut > maxCount)
                {
                    maxCount = slot.Value.CountOut;
                    res = slot.Key;
                }
            }

            return res;
        }

        internal int getUnpopularCash(Transaction.Type transactionType)
        {
            int res = 0;
            int maxCount = int.MaxValue;

            foreach (var slot in Slots)
            {
                if (transactionType == Transaction.Type.CashIn && slot.Value.CountIn < maxCount)
                {
                    maxCount = slot.Value.CountIn;
                    res = slot.Key;
                }

                if (transactionType == Transaction.Type.CashOut && slot.Value.CountOut < maxCount)
                {
                    maxCount = slot.Value.CountOut;
                    res = slot.Key;
                }
            }

            return res;
        }


    }
}
