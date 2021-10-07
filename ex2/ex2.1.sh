cp /share/ex_data/ex2/address_book.txt .
cat address_book.txt | tr "0-89\- " "1-90\t\t" | tr -s "\t" > wrong_and_reformatted.txt
sort -k2,2n -k3,4r address_book.txt  > sorted.txt
cut -f1 -d"-" address_book.txt | sort | uniq -c | sort -k1,1nr | head -n4 >> sorted.txt
cut -d" " -f2,5 address_book.txt | paste -d" " address_book.txt - | cut -d" " -f1,3,4,6,7 > address_book_israeli.txt
