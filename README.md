# System_of_modular_arithmetic
System of long-term modular arithmetic modulo N
Big Integers(*Paul Koba*)
```diff
+ ready
! not ready, problem code
- no commits on branch
**Скінченне поле**  
+  * Додавання, віднімання, множення чисел.(*Paul Koba, Oleksii Safloniuk*)  
+  * Знаходження оберненого елемента. Ділення чисел. (*Mykhaylo  Doroshenko, Ivan Ilyin*)  
+  * Швидке піднесення у степінь, використовуючи переведення числа у форму Монтгомері.(*Alex Polishchuck*)  
+  * Розклад числа на множники (наївний алгоритм та алгоритм Поларда). (*Roman Prokopchuk, Anna Kotlyarova*)  
+  * Обчислення квадратного кореня числа .(*Artem Pylypenko, Stepan Ilchuk*)  
#  * Обчислення дискретного логарифму числа.(*none*)  
+  * Знаходження порядку елемента групи. Визначення чи є елемент генератором мультиплікативної групи поля.(*Mykola Khlopyk*)  
+  * Знаходження функції Ейлера від заданого числа та функції Кармайкла від заданого числа.(*Vlad Bloshenko, David Grishchenko*)  
+  * Ймовірнісна перевірка числа на простоту (тест Міллера*Рабіна).(*Anna Bocharova, Liubomyr Hromadiuk*)   

**Кільце многочленів(Polynomial.h)**
+  * Додавання, віднімання, множення двох многочленів.(*Paul Koba, Oleksii Safloniuk*)  
+  * Знаходження похідної многочлена. Знаходження значення многочлена у точці.(*Anna Bocharova, Viktor Muzyka*) 
+  * Знаходження частки та остачі від ділення одного многочлена на інший. Знаходження НСД двох многочленів.(*Mykola Khlopyk, Anna Kotlyarova*) 
+  * Знаходження кругового многочлена заданого порядку. (*Artem Pylypenko, Ivan Ilyin*)  

**Поле многочленів**
#  * Розклад кругового многочлена на незвідні множники використовуючи многочлени Ri.(*none*)  
#  * Знаходження K незвідних многочленів заданого порядку.(*none*)  
+  * Перевірка чи є многочлен незвідним.(*Liubomyr Hromadiuk, Stepan Ilchuk*)  
+  * Додавання, віднімання, множення двох многочленів. Нормування многочлена. Швидке піднесення многочлена у степінь.(*Alex Polishchuck, Roman Prokopchuk*)  
-  * Знаходження оберненого многочлена до заданого за допомогою розширеного алгоритму Евкліда. (*Vlad Bloshenko, David Grishchenko*)  
#  * Знаходження порядку многочлена. Визначення чи є елемент генератором мультиплікативної групи розширення поля. (*none*)  
```

replace polField with polRing, add new field for modulus to polField , update student headers
!create new branch for new qt project
