using System;
namespace list_set 
{
    //класс узел
    class Node
    {
        int key; Node next;
        public int k
        {
            get
            {
                return key;
            } 
            set
            {
                key = value;
            }
        } 

        public Node n
        {
            get
            {
                return next;
            }
            set
            {
                next = value;
            }
        }
        public Node() 
        {
            key = 0; next = null;
        }
        public Node(int value)
        {
            key = value;
        }
        public void PrintKey() 
        {
            Console.Write(key);
        }
        public void PrintNext()
        {
            Console.WriteLine(next);
        }
    }
    //класс Список
    class List
    {
        Node head;

        public List() { head = null; }
        public List(Node n)
        {
            head = n;
        }
        public List(int n) 
        {
            Random rnd = new Random();
            Node q = new Node(rnd.Next(0, 100));
            head = q; n--;
            while(n>0)
            {
                AddTail(rnd.Next(0, 100));
                n--;
            }
        }
        public List(int[] a)
        {
            Node h = new Node(a[0]);
            head = h;
            for (int i = 1; i < a.Length; i++)
            {
                AddTail(a[i]);
            }
        }

        public List(List list)
        {
            Node n = new Node(list.head.k);
            head = n;
            for (Node i = list.head.n, j = head; i != null; i = i.n, j = j.n)
            {
                Node node = new Node(i.k);
                j.n = node;
            }
        }

        public Node Head
        {
            get
            {
                return head;
            }

            set
            {
                head = value;
            }

        }
///работа с node 
        //поиск node
        public Node find(int value)
        {
            Node i;
            for (i = head; i != null&&i.k != value; i = i.n) ;
            //if (i == null) Console.WriteLine("Нет такого элемента");
            return i;
        }
        //вывод
        public void Output() 
        {
            Node i;
            if (empty()) { Console.WriteLine("Список пуст"); return; }  
            for (i = head; i != null; i = i.n)
            { 
                i.PrintKey(); 
                Console.Write(' '); 
            }
            Console.Write('\n');
        }
        //ввод
        public void Input()
        {
            string[] values = Console.ReadLine().Split(new char[] { ' ' });
            Node h = new Node(Convert.ToInt32(values[0]));
            head = h;
            for(int i=1;i<values.Length;i++)
                AddTail(Convert.ToInt32(values[i]));
        }
        //сортирова пузырьком
         public void Bubblesort()
        {
            Node i1 = head;
            Node i2 = new Node();
            int n;
            for (n = 0; i1!= null; n++,i1=i1.n);
            for (int i = 0; i < n - 1; i++)
            {
                i1 = head;
                for (int j = 0; j < n - i - 1; j++, i1 = i1.n)
                    if (i1.k > i1.n.k)
                    {
                        i2 = i1.n;
                        swap(i1, i1.n);
                        i1 = i2;
                    }
            }
        }
        //смена значений
        public void swap(Node n1, Node n2)
        {
            if (n1 != head) 
            {
                Node f;
                for (f = head; f.n != n1; f = f.n);
                f.n = n2;
            };
            n1.n = n2.n;
            if (n1 == head) head = n2;
            n2.n = n1;
        }
        //добавление в голову
        public void AddHead(int value)
        {
            Node h = new Node(value);
            h.n = head; head = h;
        }
        //добавление в 
        public void AddTail(int value)
        {
            Node tail = new Node(value), i;
            if (head == null) { head = tail; return;}
            for (i = head; i.n != null; i = i.n);
            i.n = tail;
        }
        //добавление по позиции
        public void Addposition(int n, int value)
        {
            Node el = head, position = new Node(value);
            if (empty()) { Console.WriteLine("Список пуст"); return; }
            if (n == 0) { AddHead(value); return; }
            for (int i = 0; i != n - 1 && el != null; i++, el = el.n);
            if (el == null) {Console.WriteLine("Нет такой позиции"); return; }
            if (el.n == null) { el.n=position; return; }
            position.n = el.n; el.n = position;
        }
        //добавление ключа
        public void AddKey(int value, int key)
    {
            for (Node k = head; k!= null; k = k.n)
            {
                if (k.k == key)
                {
                    Node el=new Node(value);
                    el.n = k.n;
                    k.n = el;
                }
            }
    }
        //удаление головки
        public void RemoveHead()
        {
            head = head.n;
        }
        // удаление из хвоста
        public void Removetail()
        {
            if (empty()) { Console.WriteLine("Список пуст"); return; }
            if (head.n == null) { head = null; return; } 
            Node i;
            for (i = head; i.n.n != null; i = i.n) ;
            i.n = null;
        }
        // удаление по позиции
        public void RemovePosition(int n)
        {
            Node el = head;
            if (head == null) { Console.WriteLine("Список пуст"); return; }
            if (n == 0) { RemoveHead(); return;}
            for (int i = 0; i != n - 1 && el != null; i++, el = el.n);
            if (el == null&&el.n==null) { Console.WriteLine("Нет такой позиции"); return; }
            if(el.n.n == null) { el.n = null; return;}
            el.n = el.n.n;
        }
        // удаление по ключу
        public void RemoveKey(int key)
        {
            while (head!=null&&head.k == key) {head = head.n;}
            for (Node k = head; k!=null&&k.n != null; k = k.n)
            {   
                while (k.n.k == key) 
                { if (k.n.n == null) { k.n = null; return;}
                    k.n = k.n.n; 
                }
            }
        }
        //поиск минимального
        public int min() 
        {
            int min = head.k;
            for(Node i = head; i != null; i = i.n) 
            {
                if (i.k < min) min = i.k;   
            }
            return min;
        }
        //поиск максимального
        public int max()
        {
            int max=head.k;
            for(Node i=head; i!=null; i=i.n)
            {
                if (i.k > max) max = i.k;
            }
            return max;
        }
        //проверка на пустоту
        public bool empty()
        {
            if (head == null) return true;
            return false;
        }
        // очистка списка
        public void clear()
        {
            while (head != null) head = head.n;
        }

        //перегрузка =
        public void assigment(List list)
        {
            Node n= new Node(list.head.k);
            head = n;
            for(Node i=list.head.n, j=head; i!=null; i=i.n, j=j.n)
            {
                Node node = new Node(i.k);
                j.n = node;
            }
        }

        //взятие по индексу
        public int this[int k]
        {
            get
            {
                Node j=head;
                for (int i = 0; i < k&&j!=null; i++, j = j.n) ;
                if (j == null) { Console.WriteLine("Нет такого элемента"); return(0);}
                return (j.k);
            }
            set
            {
                Node j = head;
                for (int i = 0; i < k && j != null; i++, j = j.n) ;
                if (j == null) { Console.WriteLine("Нет такого элемента");}
                j.k=value;
            }
        }
        //перегрузка
        public static List operator +(List list, List list_2)
        {
            List newlist= new List(), newlist_2=new List();
            newlist.assigment(list_2);
            newlist_2.assigment(list);
            Node i;
            for (i = newlist.head; i.n != null; i = i.n) ;
            i.n = newlist_2.head;
            return newlist;
        }
        //перегрузка
        public static List operator -(List list, List list_2)
        {
            List newlist = new List(), newlist_2=new List();
            newlist.assigment(list);
            newlist_2.assigment(list_2);
            Node i;
            for (i = newlist.head; i.n != null; i = i.n) ;
            i.n = newlist_2.head;
            return newlist;
        }
        //перегрузка
        public static bool operator ==(List list, List list_2)
        {
            for(Node i=list.head, j=list_2.head; i!=null&&j!=null;i=i.n,j=j.n)
            {
                if (i.k != j.k) return false;
            }
            return true;
        }
        //перегрузка
        public static bool operator !=(List list, List list_2)
        {
            Node i, j;
            for (i = list.head, j = list_2.head; i != null && j != null; i = i.n, j = j.n)
            {
                if (i.k != j.k) return true;
            }
            if (i == null && j != null || j == null && i != null) return true;
            return false;
        }

    }
    ///начало 4 лабы

    class Set : List
    {
        int cardinality;

        public Set():base()
        {
            cardinality = 0;
        }

        public int c
        {
            get
            {
                return cardinality;
            }
            set
            {
                cardinality = value;
            }
        }

        public Set(List list)
        {
            Node h = new Node(list.Head.k), j = new Node();
            Head = h; cardinality = 1;
            for (Node i = list.Head.n; i != null; i = i.n)
            {
                for (j = Head; j.n != null && j.k != i.k; j = j.n) ;
                if (j.n == null && j.k != i.k) { Node node = new Node(i.k); j.n = node; cardinality++; }
            }
        }

        public Set(int n)
        {
            Random rnd = new Random();
            int value;
            for (cardinality = 0; cardinality != n;)
                if (find(value = rnd.Next(0, 100)) == null)
                {
                    AddElement(value);
                }
        }
        //ввод
        public new void Input()
        {
            string[] values = Console.ReadLine().Split(new char[] { ' ' });
            Node h = new Node(Convert.ToInt32(values[0]));
            Head = h; cardinality = 1;
            for (int i = 1; i < values.Length; i++)
                if (find(Convert.ToInt32(values[i])) == null)
                {
                    AddTail(Convert.ToInt32(values[i]));
                    cardinality++;
                }
        }
        //перегрузка =
        public void assigment(Set set)
        {
            assigment((List)set); cardinality = set.cardinality;
        }
        //перегрузка сравнения
        public static bool operator ==(Set set1, Set set2)
        {
            if (set1.cardinality != set2.cardinality) return false;
            for (Node i = set1.Head; i != null; i = i.n)
                if (set2.find(i.k) == null) return false;
            return true;
        }
        //перегрузка сравнения
        public static bool operator !=(Set set1, Set set2)
        {
            if (set1.cardinality != set2.cardinality) return true;
            for (Node i = set1.Head; i != null; i = i.n)
                if (set2.find(i.k) == null) return true;
            return false;
        }
        //перегрузка +
        public static Set operator +(Set set_1, Set set_2)
        {
            Set set = new Set((List)set_1 + (List)set_2); return set;
        }
        //перегрузка -
        public static Set operator -(Set set, int value)
        {
            Set result = new Set(set);
            if (result.find(value) == null)
            {
                Node node = new Node(value), i = new Node();
                for (i = result.Head; i.n != null; i = i.n) ;
                i.n = node;
            }
            result.cardinality++;
            return result;
        }
        //перегрузка *
        public static Set operator *(Set set1, Set set2)
        {
            Set result = new Set();
            Node i = new Node(), j = new Node();
            for (i = set1.Head; i != null; i = i.n)
            {
                for (j = set2.Head; j != null && i.k != j.k; j = j.n) ;
                if (j != null && i.k == j.k) { result.AddTail(i.k); result.cardinality++; }
            }
            return (result);
        }
        //перегрузка /
        public static Set operator /(Set set1, Set set2)
        {
            Set result = new Set(set1);
            for (Node i = result.Head; i != null; i = i.n)
            {
                if (set2.find(i.k) != null) result.RemoveKey(i.k);
            }
            return result;
        }
        //добавление элемента
        public void AddElement(int value)
        {
            if (find(value) == null) { AddTail(value); cardinality++; }
        }
        //Пересечение
        public void Intersection(Set set2)
        {
            for (Node i = Head; i != null; i = i.n)
                if (set2.find(i.k) == null) RemoveKey(i.k); 
        }
        //разность 
        public void complement(Set set2)
        {
            for (Node i = Head; i != null; i = i.n)
            {
                if (set2.find(i.k) != null) RemoveKey(i.k);
            }
        }
        //удаление ключа
        public new void RemoveKey(int value)
        {
            if (find(value) != null)
            {
                base.RemoveKey(value); cardinality--;
            }
        }
        //удаление значения
        public Set Removevalue(int value)
        {
            Set set = new Set(this);
            if (set.find(value) != null)
            {
                set.RemoveKey(value); set.cardinality--;
            }
            return set;
        }
        //удаление элемента из множества
        public static Set operator ~(Set set1)
        {
            Set newset = new Set();
            int n = 100;
            for (int i = 0; i < n; i++)
                if (set1.find(i) == null) newset.AddElement(i);
            return newset;
        }
    }



    class Program
    {
        static void check() //проверка списка
        {
            Console.WriteLine("Проверки на Список");
            Console.WriteLine("первая проверка");
            List s1 = new List();
            s1.AddHead(1); s1.AddTail(10);
            s1.Output();
            Console.WriteLine("вторая проверка");
            List s2 = new List(6);
            s2.Output(); 
            int min = s2.min(), max=s2.max();
            Console.WriteLine("Минимум - " + min + " Максимум - " + max);
            s2.Bubblesort(); s2.Output();
            Console.WriteLine("третья проверка");
            int el = s2[1]; Console.WriteLine(el); 
            s2.RemovePosition(1);
            s2.Output();
            Console.WriteLine("четвертая проверка");
            el = s2[6]; s2.Removetail(); s2.Output();
            Console.WriteLine("пятая проверка");
            List s3 = new List(); s3.assigment(s1);
            s3.Output();
            if (s1 == s3) Console.WriteLine("Списки равны");
            Node a = new Node();
            a = s3.find(15);
            Console.WriteLine("шестая проверка");
            s3.RemoveHead(); s3.RemoveKey(10); s3.Output(); if(s3.empty()) Console.WriteLine("s3 пуст");
            Console.WriteLine("седьмая проверка");
            int[] b = new int[6]; Random rnd = new Random();
            for (int i = 0; i < b.Length; i++) { b[i] = rnd.Next(0, 20); Console.Write(b[i] + " "); }
            Console.Write("\n");
            List s4 = new List(b); s4.Output(); s4.find(25);
            s4.Addposition(3, 25); s4.Output();
            Console.WriteLine("восьмая проверка");
            List s5 = new List(s2); s5.Output();
            if (s5.find(4) != null) s5.RemoveKey(4);
            else s5.AddTail(4);
            s5.Output();
            Console.WriteLine("девятая проверка");
            int val=0;
            for (int i = 0; i < 4; i++)
            {
                val = Int32.Parse(Console.ReadLine());
                s5.AddTail(val);
            }
            s5.Output();
            if (s5 == s4) Console.WriteLine("Равны");
            else Console.WriteLine("Не равны");
            Console.WriteLine("десятая проверка");
            s5 = s5 - s4 + s1;
            s5.Output();
        }

        static void CheckSet()
        {   Console.WriteLine("");
            Console.WriteLine("");
            Console.WriteLine("Проверки на множество");
            Console.WriteLine("Проверка 1");
            Set s1 = new Set(10); s1.Output();
            Console.WriteLine("Проверка 2");
            Set s2 = new Set(s1); s2.Output();
            if (s1 == s2) Console.WriteLine("Равны");
            Console.WriteLine("Проверка 3");
            Set s3 = new Set(s1);
            if (s1.find(5) == null) s3.AddElement(5);
            else s3.RemoveKey(5);
            s3.Output(); if (s1 != s3) Console.WriteLine("Не равны");
            Console.WriteLine("Проверка 4");
            Set s4 = new Set(); s4.empty(); s4.AddElement(5); s4.AddElement(10); s4.AddElement(15); s4.AddElement(5); s4.Output();
            Console.WriteLine("Проверка 5");
            Set s5 = new Set(); s5.assigment(s4); if (s5.find(15) != null) s5.RemoveKey(15);
            s5.Output();
            Console.WriteLine("Проверка 6");
            List T = new List(20); T.Output(); Set s6 = new Set(T); s6.Output(); Console.WriteLine("Мощность множества равна " + s6.c);
            Console.WriteLine("Проверка 7");
            Set s7 = ~s6; s7.Output(); s6.Output(); Set s8 = s7 * s6; s8.Output();
            Console.WriteLine("Проверка 8");
            Set s9 = new Set(); s9.Input(); s7.Output(); Set V1 = s7 * s9; V1.Output();
            Set V2 = s7 + s9; V2.Output(); Set v3 = s7 / s9; v3.Output();
            Console.WriteLine("Проверка 9");
            V1 = V1 + v3; V1.Output();
            if (V1 == s7) Console.WriteLine("Равны");
            else Console.WriteLine("Не равны");
            Console.WriteLine("Проверка 10");
            V2.Output(); v3.Output();
            V2.complement(v3); V2.Output();
            s9.Output();
            if(V2==s9) Console.WriteLine("Равны");
            else Console.WriteLine("Не равны");
        }
        public static void Main()
        {
            
            check();
            CheckSet();
        }
    }
}