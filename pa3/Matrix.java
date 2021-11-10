// --------------------------------------------------------------------------------
// Matrix ADT
// --------------------------------------------------------------------------------
@SuppressWarnings("overrides")
class Matrix{
    private class Entry{
    int column;
    double value;
     
       Entry(int column, double value){
          this.column = column;
          this.value = value;
       }
 
       public boolean equals(Object x){
       boolean val = false;
       Entry E;
          if(x instanceof Entry){
             E = (Entry)x;
             val = (this.value == E.value);
          }
       return val;
       }

       public String toString(){
       StringBuffer sb = new StringBuffer();
       sb.append("("+this.column+", "+this.value+ ")");
       return new String(sb);
       }
    }
    
    
 List matrix[];
 int non_zero;
 
 // Matrix
 // Constructor 
 // Makes a new n x n zero Matrix.
 // pre: n>= 1
 Matrix(int n){
    if(n < 1){
       throw new RuntimeException(
	 "Matrix Error: Must pass n >= 1 into Constructor");
    }
 this.matrix = new List[n+1];
 this.non_zero = 0;
    for (int i = 0; i < n+1; i++){
       matrix[i] = new List();
    }
 }

 // getSize()
 // Returns n, the number of rows and columns of this Matrix
 int getSize(){
 return this.matrix.length-1;
 } 
 
 // getNNZ
 // Returns the number of non-zero entries in this Matrix
 int getNNZ(){
 return non_zero;
 }

 // equals
 // Overrrides Object's equals() method
 public boolean equals(Object x) {
 boolean val = false;
    if(!(x instanceof Matrix)){
       return false;
    }
 Matrix M = (Matrix)x;
    if(this.getSize() != M.getSize()){
       return false;
    }
    if(this.getNNZ() != M.getNNZ()){
        return false;
    }
 Entry current;
 Entry temp;   
 
    for(int i = 1; i < this.getSize()+1; i++){
       if(this.matrix[i].length() != 0 && M.matrix[i].length() != 0){
          this.matrix[i].moveFront();
          M.matrix[i].moveFront();
             if(this.matrix[i].length() != M.matrix[i].length()){
	        return false;
	     }
           while(this.matrix[i].index() != -1 && M.matrix[i].index() != -1){
              current = (Entry)this.matrix[i].get();
              temp = (Entry)M.matrix[i].get();
	         if(!(current.equals(temp))){
                    return false;
                 }
              this.matrix[i].moveNext();
              M.matrix[i].moveNext();
           }
       }
    }
 return true;
 }

 // makeZero
 // sets this Matrix to the zero state
 void makeZero(){
    for(int i = 0; i < this.getSize(); i++){
       this.matrix[i].clear();
    }
    this.non_zero = 0;
 }

 // copy
 // returns a new Matrix having the same entries as this Matrix
 Matrix copy(){
 Matrix newCopy = new Matrix(this.getSize());
 Entry temp = null;
 
    for(int i = 1; i < this.getSize()+1; i++){
          if(this.matrix[i].length() != 0){
             this.matrix[i].moveFront();
             for (int k = 0; k < this.matrix[i].length(); k++){
                temp = (Entry)this.matrix[i].get();
                newCopy.changeEntry(i,temp.column,temp.value);
                this.matrix[i].moveNext();
             }
	  }
    }
 return newCopy;
 }

 // changeEntry
 // Changes ith row, jth column of this Matrix to x
 // pre: 1<=i<=getSize(), 1<=j<=getSize()
 void changeEntry(int i, int j, double x){
 Entry temp = null;
 Entry insert = null;
    if(i <= 0){
       throw new RuntimeException(
	 "Matrix Error: Cannot have row value less than 1");
    }
    if(i > this.getSize()){
       throw new RuntimeException(
	 "Matrix Error: Cannot pass row value greater than Matrix size");
    }
    if(j <= 0){
       throw new RuntimeException(
	 "Matrix Error: Cannot pass column value less than 1");
    }
 
    if(j > this.getSize()){
       throw new RuntimeException(
	 "Matrix Error: Cannot pass column value greater than Matrix size");
    }
    if(this.matrix[i].length() == 0){
       if(x == 0){
          return;
       }
       else{ 
          insert = new Entry(j,x);
          this.matrix[i].append(insert);
          this.non_zero++;
       }
    }
    else{
        this.matrix[i].moveFront();
        while(this.matrix[i].index() != -1){
           temp = (Entry)this.matrix[i].get();
              if(temp.column == j){
                 if(x == 0){
                    this.matrix[i].delete();
                    this.non_zero--;
                    return;
                 }
                 else{
                    temp.value = x;
                    return;
                 }
              }
              else if(j < temp.column){
                 if(x == 0){
                    return;
                 }
                    insert = new Entry(j,x);
                    this.matrix[i].insertBefore(insert);
                    this.non_zero++;
                    return;
              }
              else if(this.matrix[i].back() == this.matrix[i].get()){
                 if(x == 0){
                    return;
                 }
                 insert = new Entry(j,x);
                 this.matrix[i].append(insert);
                 this.non_zero++;
                 return;   
              }
           this.matrix[i].moveNext(); 
        } 
   }
 }

 // scalarMult
 // returns a new Matrix that is the scalar product of this Matrix with x
 Matrix scalarMult(double x){
 Matrix M = new Matrix(this.getSize());
 Entry temp = null;
    for(int i = 1; i < this.getSize()+1; i++){ 
       if(this.matrix[i].length() != 0){
       this.matrix[i].moveFront();
          while(this.matrix[i].index() != -1){
             temp = (Entry)this.matrix[i].get();
             M.changeEntry(i,temp.column,temp.value*x); 
             this.matrix[i].moveNext(); 
          }
       }     
    }
 return M;
 }

 // add
 // returns a new Matrix that is the sum of this Matrix with M
 // pre: getSize() == M.getSize()
 Matrix add(Matrix M){
 Matrix resultM = null;
 List resultAdd = null;
 Entry temp = null;
    if(this.getSize() != M.getSize()){
       throw new RuntimeException(
          "Matrix Error: Must pass matrices with same dimensions");
    }
 resultM = new Matrix(this.getSize());
    for(int i = 1; i < this.getSize()+1; i++){
       resultAdd = listAdd(this.matrix[i],M.matrix[i]);
          if(resultAdd.length() != 0){
          resultAdd.moveFront();
             while(resultAdd.index() != -1){
                temp =(Entry)resultAdd.get();
                resultM.changeEntry(i,temp.column,temp.value);
                resultAdd.moveNext();
             }
          }
    }
 return resultM;
 }

 // sub
 // returns a new Matrix that is the difference of this Matrix with M
 // pre: getSIze() == M.getSize() 
 Matrix sub(Matrix M){
 Matrix resultM = null;
 List resultSub = null;
 Entry temp = null;
    if(this.getSize() != M.getSize()){
       throw new RuntimeException(
	  "Matrix Error: Must pass matrices with same dimensions");
    }
 resultM = new Matrix(this.getSize());
    for(int i = 1; i < this.getSize()+1; i++){
       resultSub = listSub(this.matrix[i],M.matrix[i]);
          if(resultSub.length() != 0){
             resultSub.moveFront();
                while(resultSub.index() != -1){
                   temp = (Entry)resultSub.get();
                   resultM.changeEntry(i,temp.column,temp.value);
                   resultSub.moveNext();
                }
          }
    }
 return resultM;
 }

 // transpose
 // returns a new Matrix that is the transpose of this Matrix
 Matrix transpose(){
 Matrix M = null;
 Entry temp = null;
 int k = 0;
    if(this.matrix == null){
       throw new RuntimeException(
	  "Matrix Error: Cannot call transpose on NULL Matrix");
    }
    if(this.non_zero == 0){
       M = new Matrix(this.getSize());
       return M;
    }
 M = new Matrix(this.getSize());
    for(int i = 1; i < this.getSize()+1; i++){
       if(this.matrix[i].length() != 0){
          this.matrix[i].moveFront();
          while(k != this.matrix[i].length() && this.matrix[i].index() != -1){
             temp = (Entry)this.matrix[i].get();
             M.changeEntry(temp.column,i,temp.value);
             this.matrix[i].moveNext();
             k++;
          }
          k = 0;
       }
    }
 return M;
 }

 // mult
 // returns a new Matrix that is the product of this Matrix with M
 // pre: getSize()==M.getSize()
 Matrix mult(Matrix M){
 Matrix result = null;
 double product;
    if(this.getSize() != M.getSize()){
       throw new RuntimeException(
	  "Matrix Error: Must pass matrices with proper dimensions");
    }
 result = new Matrix(this.getSize());
 M = M.transpose();
    for(int i = 1; i < this.getSize()+1; i++){
       for(int j = 1; j < this.getSize()+1; j++){
          product = dot(this.matrix[i],M.matrix[j]);
             if(product != 0){
                result.changeEntry(i,j,product);
             }
       }
    }
 return result;
 } 

 // dot
 // Helper Function
 // Caluclates product of two matrices
 private static double dot(List P, List Q){
 Entry tempP = null;
 Entry tempQ = null;
 double product = 0;
    if(P.length() == 0 || Q.length() == 0){ 
       return product;
    }
    if(P.length() != 0 && Q.length() != 0){
       P.moveFront();
       Q.moveFront();
       while(P.index() != -1 && Q.index() != -1){
          tempP = (Entry)P.get();
          tempQ = (Entry)Q.get(); 
             if(tempP.column == tempQ.column){
                product += tempP.value*tempQ.value;  
                if(tempP == tempQ){ 
                   P.moveNext();
		}
		else{
		   P.moveNext();
                   Q.moveNext();
		}
             }
             else if(tempP.column < tempQ.column){
                P.moveNext(); 
             }
             else{
                Q.moveNext();
             }
       }
    }
 return product;
 }

 // listAdd
 // Helper Function
 // Computes the sum of two Matrices
 private List listAdd(List P, List Q){
 List result = new List();
 Entry tempP = null;
 Entry tempQ = null;
 Entry temp = null;
    if(P.length() == 0 && Q.length() == 0){
       return result;
    }
    if(P.length() != 0 && Q.length() == 0){
       P.moveFront();
          while(P.index() != -1){
             tempP = (Entry)P.get();
             result.append(tempP);
             P.moveNext();
          }
    return result;
    }
    if(P.length() == 0 && Q.length() != 0){
       Q.moveFront();
          while(Q.index() != -1){
             tempQ = (Entry)Q.get();
             result.append(tempQ);
             Q.moveNext();
          }
    return result;
    }
    if(P.length() != 0 && Q.length() != 0){
       P.moveFront();
       Q.moveFront();
          while(P.index() != -1 && Q.index() != -1){
             tempP = (Entry)P.get();
             tempQ = (Entry)Q.get();
                if(tempP.column == tempQ.column){
                   temp = new Entry(tempP.column, tempP.value + tempQ.value);
                   result.append(temp);
                      if(tempP == tempQ){
		         P.moveNext();
                      }
                      else{
                         P.moveNext();
                         Q.moveNext(); 
                      }
		}
                else if(tempP.column < tempQ.column){
                   temp = new Entry(tempP.column, tempP.value);
                   result.append(temp);
		   P.moveNext(); 
                }
                else if(tempP.column > tempQ.column){
                   temp = new Entry(tempQ.column, tempQ.value);
                   result.append(temp);
		   Q.moveNext();
                }
          }
          while(P.index() != -1){
             tempP = (Entry)P.get();
             result.append(tempP);
             P.moveNext();
          } 
          while(Q.index() != -1){
             temp = (Entry)Q.get();
             result.append(tempQ);
             Q.moveNext();
          }
    }
 return result;
 }

 // listSub
 // Helper Function
 // Computes the difference between Matrices
 private List listSub(List P, List Q){
 List result = new List();
 Entry tempP = null;
 Entry tempQ = null;
 Entry temp = null;
 double diff = 0;
    if(P.length() != 0 && Q.length() == 0){
       P.moveFront();
       while(P.index() != -1){
          tempP = (Entry)P.get();
          result.append(tempP);
          P.moveNext();
       }
    return result;
    }
    if(P.length() == 0 && Q.length() != 0){
       Q.moveFront();
          while(Q.index() != -1){
             tempQ = (Entry)Q.get();
             diff = 0 - tempQ.value;
             temp = new Entry(tempQ.column, diff);
             result.append(temp);
             Q.moveNext();
          }
    return result;
    }
    if(P.length() != 0 && Q.length() != 0){
       P.moveFront();
       Q.moveFront();
          while(P.index() != -1 && Q.index() != -1){
             tempP = (Entry)P.get();
             tempQ = (Entry)Q.get();
             if(tempP.column == tempQ.column){
                diff = tempP.value - tempQ.value;
                if(diff != 0){
                   temp = new Entry(tempP.column,diff);
                   result.append(temp);
                }
		   if(tempP == tempQ){
		      P.moveNext();
		   }
		   else{
                      P.moveNext();
                      Q.moveNext();
		   }
             }
             else if(tempP.column < tempQ.column){
                if(tempP.value != 0){
                   //temp = new Entry(tempP.column,tempP.value);
                   result.append(tempP);
                }
                P.moveNext();
             }
             else{
                if(tempQ.value != 0){
                   diff = 0 - tempQ.value;
                   temp = new Entry(tempQ.column, diff);
                   result.append(temp);
                }
	     Q.moveNext();
	     }
          }
    }
    while(P.index() != -1){
       tempP = (Entry)P.get();
       result.append(tempP);
       P.moveNext();
    }
    while(Q.index() != -1){
       tempQ = (Entry)Q.get();
       diff = 0 - tempQ.value;
       temp = new Entry(tempQ.column,diff);
       result.append(temp);
       Q.moveNext();
    }
 return result;
 }

 // toString
 // Overrides String toString method
 public String toString(){
 StringBuffer sb = new StringBuffer();
 Entry temp = null;
    for(int i = 1; i < this.getSize()+1; i++){
       if(this.matrix[i].length() != 0){
          this.matrix[i].moveFront();
          sb.append(i+": ");
          while(this.matrix[i].index() != -1){
             temp = (Entry)this.matrix[i].get();
             sb.append(temp);
             sb.append(" ");
             this.matrix[i].moveNext();
          }
       sb.append("\n");
       }
    }
 return new String(sb);
 }

}

