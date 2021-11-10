//--------------------------------------------------------------------------
// Lex.java
// Counts the number of lines in an input file and creates a String Array to
// hold the Strings and a List object to represent an indirectly ordered List
//--------------------------------------------------------------------------
// count the amout of lines in the file to find size of Array
// line number will represent index of String
// use line numbers for element to insert into List 

import java.io.*;
import java.util.Scanner;

class Lex{
 public static void main(String[] args) throws IOException{
      Scanner in = null;
      Scanner read = null;
      PrintWriter out = null;
      String line = null;
      int n = 0;
      int i = 0;
      int cursor = -1;
      int lineNum = 0;
      String list[] = null;
      List L = new List();

      if(args.length < 2){
         System.err.println("Usage: Lex infile outfile");
         System.exit(1);
      }
      
      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));

      while( in.hasNextLine()){
         n++;   
         in.nextLine();
      }
      list = new String[n];
      read = new Scanner(new File(args[0]));
      // use lineNum to keep track of element index 
      while(read.hasNextLine()){
         line = read.nextLine();
         list[lineNum] = line;
         
         if(L.length()==0){ 
            L.append(lineNum); 
         }         
         else{ 
         L.moveFront(); 
            while(i < lineNum){
               String s1 = list[lineNum]; // new word that is getting compared
               String s2 = list[L.get()];       // word in list, iterate through this one
                  if(s1.compareTo(s2)>0){
                     if(L.index()+1 == L.length()){
                     L.append(lineNum);
                     }
                     L.moveNext();
                     i++;
                  }  
                  else if(s1.compareTo(s2)<0){  
                  L.insertBefore(lineNum);
                  break;
                  }         
            }
         }
      i = 0;
      lineNum++;
         
      }
      L.moveFront();
      for(int k=0; k < L.length(); k++){
         cursor = L.get();
         out.println(list[cursor]);
         L.moveNext();
      } 
      read.close();
      in.close();
      out.close();
   }
 }
