using System;
using System.Collections.Generic;
using System.Text;

namespace Bankomat
{
    class Slot
    {
        int count, countIn, countOut;
        public int Nominal { get; }
        public int Count { get { return count; } }
        public int OptCount { get; }

        public int CountIn { get { return countIn; } }
        public int CountOut { get { return countOut; } }

        public Slot(int nominal, int count=0, int optCount=100)
        {
            Nominal = nominal;
            this.count = count;
            OptCount = optCount;
        }

        public bool Deposit(int count)
        {
            if (count > 0) this.count += count;
            countIn += count;
            return true;
        }

        public bool Withdraw(int count)
        {
            if (count > 0 && count >= Count)
            {
                this.count -= count;
                countOut += count;
                return true;
            }
            return false;
        }

        public bool CanWithdraw(int count)
        {
            return (count > 0 && count <= Count);
        }

        internal void ResetCounts()
        {
            countIn = 0;
            countOut = 0;
        }
    }
}
