using System;
using System.Text.RegularExpressions;
class HelloWorld
{
static int CharInString(string first_str){
        Console.Write("Введите свой символ: ");
        string my_char = Console.ReadLine();
        int first_len = first_str.Length;
        first_str = first_str.Replace(my_char, "");
        int end_len = first_str.Length; 
        return first_len-end_len;
    
}

static string DeleteNUMInStr(string first_str){
for (int i=0;i<10; i++){
    first_str = first_str.Replace(Convert.ToString(i), "");
}
return first_str;
}
static bool CharInKey(string first_str){
    Console.Write("Введите свою строку: ");
    string? key = Console.ReadLine();
    for (int i = 0; i<(key.Length); i++){
        int indexOfChar = first_str.IndexOf(key[i]); // равно 4
        //Console.WriteLine(indexOfChar);
        if (indexOfChar == -1){
            return false;
        }
    }
    return true;
}
static void ScobInStr(string first_str){
    int sum=0;
    int indexOfChar2 = first_str.IndexOf(")");
    int indexOfChar1 = first_str.IndexOf("(");
    if (indexOfChar1>indexOfChar2){
        Console.WriteLine("Скробки раставлены неправильно");
        return;
    }
    for (int i =0; i< first_str.Length; i++){
        
        if (first_str[i] == Convert.ToChar("(")){
             sum+=1;
        }else if (first_str[i] == Convert.ToChar(")")){
            sum -=1;
        }
    }
    if (sum != 0){
        Console.WriteLine("Скробки раставлены неправильно");
    } else{
        Console.WriteLine("Скробки раставлены правильно");
    }
    
}
static void Main(string[] args)
    {   //ввод строки
        Console.Write("Введите свою строку: ");
        string? first_str = Console.ReadLine();
        Console.WriteLine("Что вы хотите сделать?");
        Console.WriteLine("1 - чтобы посчитать вхождение символа");
        Console.WriteLine("2 - чтобы удалить все цифры");
        Console.WriteLine("3 - чтобы выяснить встречаются ли буквы в ключе");
        Console.WriteLine("4 - проверка на расставление скобок");
        int flag_is_comsnd = Convert.ToInt32(Console.ReadLine());
        if (flag_is_comsnd == 1){
            //1 задание
            int sum = CharInString(first_str);
            Console.WriteLine(sum);
        } else if(flag_is_comsnd == 2){
              //2 задание
            first_str = DeleteNUMInStr(first_str);
            Console.WriteLine(first_str);
        }else if(flag_is_comsnd == 3){
              // задание 3
            bool res = CharInKey(first_str);
            Console.Write(res);
        }else if (flag_is_comsnd == 4){
            ScobInStr(first_str);
        } else{
            Console.WriteLine("Незнакомый выбор! Будьте внимательнее!!!");
        }      
}}
