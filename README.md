<h1> Final Project: String Search I </h1>

Group Members: Nadia Sousa, Yashaswini Mandalam, Sean Phelan, Wyatt Polasek


<h2> Project Summary </h2>
Our project is an implementation of the Rabin Karp and Boyer Moore string search algorithms. The Rabin Karp algorithm finds a string in a file by using a rolling hash method. The Boyer Moore algorithm uses preprocessing on the string to be found and creates shift tables to find the string in a file. We have provided three source files to search from: 100000 letter DNA sequence file (contains A, C, G and Ts), 100000 digits of pi and a random letters and numbers file. Of course this code can be used to find a string in any other file as well. 





<h2> Rabin-Karp Algorithm </h2>
The Rabin-Karp Algorithm was created in 1987 by Micheal O. Rabin and Richard M. Karp. This string search algorithm uses a rolling hash to find a string in a text. A more detailed and clear explaination of this algorithm is provided in our project report, so please look through that. The average and best case time complexity of the algorithm is O(m+n) where m is the length of the string and n is the length of the text that is being searched through.


<h2> Boyer Moore Algorithm </h2>
The Boyer Moore Algorithm was created in 1977 by Robert S. Boyer and J Strother Moore. This algorithm performs search by predetermining the shifts when a mismatch occurs between the pattern and the text that is being searched. The shifts are determined using two rules: the bad character rule and good suffix rule. A clear explaination of this algorithm and both these rules are provided in the project report. 


<h2> Inputs </h2>
The input to our project is the name of the file that is being searched, the word that we are trying to find and the name of the algorithm the user wants to use to perform the string search. Please look at the "How To" section for details on how to pass this information to the program. 


<h2> Outputs </h2>
<p>
Our code out puts the number of occurnces of the string in the file and also the time it took to perform the search.
An example output would look something like this: 

</p>
<kbd>
<img align = "center" height = 100 width = 500 src = "https://user-images.githubusercontent.com/85038009/205728866-17450026-7281-49b7-b810-f41a3d833411.png" />
</kbd>

<h2> How to: </h2>
Instructions on how to compile this program are shown below

Note that the first command is the filename, the second is the string and third is the algorithm the user wants to use

For Rabin Karp
```
g++ stringSearch.cpp -o stringSearch
./stringSearch Sample1.txt xYz rb
```
For Boyer Moore
```
g++ stringSearch.cpp -o stringSearch
./stringSearch Sample1.txt xYz bm
```
