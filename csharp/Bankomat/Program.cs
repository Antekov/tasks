using System;
using System.Collections.Generic;

namespace Bankomat
{
    class Program
    {
        static void Main(string[] args)
        {
            // Создаем администратора и обычных клиентов банка
            Client c0 = new Client("Administrator", 0);
            Client c1 = new Client("John Smith", 10000);
            Client c2 = new Client("Denis Goldman", 150000);
            Client c3 = new Client("Sam Jackson", 20000);

            // Создаем банк
            Bank bank = new Bank();

            // Добавляем администратора и клиентов в банк 
            bank.addAdmin(c0);
            bank.addClient(c1);
            bank.addClient(c2);
            bank.addClient(c3);

            // Выдаем карты клиентам
            bank.emitCard(c0, Card.Type.Debit);
            bank.emitCard(c1, Card.Type.Debit);
            bank.emitCard(c1, Card.Type.Credit);
            bank.emitCard(c2, Card.Type.Debit);
            bank.emitCard(c2, Card.Type.Debit);
            bank.emitCard(c3, Card.Type.Debit);
            bank.emitCard(c3, Card.Type.Credit);

            // Создаем банкомат
            Bankomat ATM = new Bankomat(bank);

            // Создаем набор купюр для загрузки в виде словаря номинал -> количество
            Dictionary<int, int> cash = new Dictionary<int, int>();
            cash.Add(50, 200);
            cash.Add(100, 200);
            cash.Add(200, 200);
            cash.Add(500, 200);
            cash.Add(1000, 200);
            cash.Add(2000, 200);

            // Загружаем купюры в слоты банкомата
            ATM.LoadCash(cash);
            
            // Запускаем банкомат
            ATM.Start();
        }
    }
}
