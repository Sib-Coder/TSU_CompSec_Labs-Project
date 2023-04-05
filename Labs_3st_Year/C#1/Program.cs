using System;
 
class HelloWorld
{
static int Pow(int a, int b){
   int c=a,f=a;
    for(int i=1;i<b;i++){
        for(int j=1;j<a;j++){
            c+=f;//просто возвели в степень
        }
        f=c;//ввели добавку на степень
    }
    return c;
}

static void Main(string[] args)
    {   //ввод а
        Console.Write("Введите свое a: ");
        int a = Convert.ToInt32(Console.ReadLine());
        
        Console.Write("Введите свое k: ");
        //ввод к
        int k = Convert.ToInt32(Console.ReadLine());

        int sum = 0;
        
        if (a == 0){
             Console.WriteLine($"Итого: 1");
        }else if(k == 0){
            Console.WriteLine($"Итого: 1");
            
        }else if(a< 0){
            a=a*(-1);
            if (k%2==0){
                sum = Pow(a,k);
                Console.WriteLine($"Итого: {sum}");
            }else {
                sum= Pow(a,k)*(-1);
                Console.WriteLine($"Итого: {sum}");
            }
        }
        else{
            //итоговое значение
            sum +=Pow(a, k);
            Console.WriteLine($"Итого: {sum}");
        }
        
        
 
    }
}