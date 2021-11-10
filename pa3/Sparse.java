// -----------------------------------------------------------------------------------
// Sparse.java
// Takes integer values from user input and instantiates the sparse Matrices and 
// populates Matrix entries. Then, the program performs vairou Matrix operations on the
// Matrices that have been instantiated.
// -----------------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;

class Sparse{
 public static void main(String args []) throws IOException{ 
      Scanner in = null;
      //Scanner read = null;
      PrintWriter out = null;
      int n = 0,nnzA = 0,nnzB = 0;
      int i = 0, j = 0, k = 0;
      double value = 0;
      String line;
      Matrix A = null;
      Matrix B = null;
      if(args.length < 2){
         System.err.println("Usage: Sparse infile outfile");
         System.exit(1);
      }
      
      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1])); 
      while( in.hasNext()){
         if(A == null && B == null){ 
            n = in.nextInt();   
            nnzA = in.nextInt();
            nnzB = in.nextInt();
            A = new Matrix(n);
            B = new Matrix(n);
         }
         else{
            if(k < nnzA){ 
                  i = in.nextInt();
                  j = in.nextInt();
                  value = in.nextDouble();
                  A.changeEntry(i,j,value);
                  k++;
            }
            else{
               i = in.nextInt();
               j = in.nextInt();
               value = in.nextDouble();
               B.changeEntry(i,j,value);
            }
         }
      }
      out.println("A has "+A.getNNZ()+" non-zero entries:");
      out.println(A);
      out.println("B has "+B.getNNZ()+" non-zero entries:");
      out.println(B);

      Matrix C = A.scalarMult(1.5);
      out.println("(1.5)*A =");
      out.println(C);
       
      Matrix D = A.add(B);
      out.println("A+B =");
      out.println(D);
      
      Matrix E = A.add(A);
      out.println("A+A =");
      out.println(E);
 
      Matrix F = B.sub(A);
      out.println("B-A =");
      out.println(F);
  
        
      Matrix H = A.sub(A);
      out.println("A-A =");
      out.println(H);
   
      Matrix G = A.transpose();
      out.println("Transpose(A) =");
      out.println(G);
      
      Matrix I = A.mult(B);
      out.println("A*B =");
      out.println(I);
      
      Matrix J = B.mult(B);
      out.println("B*B =");
      out.println(J);

      in.close();
      out.close();
 }
}
