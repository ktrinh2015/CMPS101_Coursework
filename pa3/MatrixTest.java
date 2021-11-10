public class MatrixTest{
 public static void main(String args[]){
 int n = 3;
 Matrix A = new Matrix(n);
 
 A.changeEntry(1,1,1);
 A.changeEntry(1,2,2);
 A.changeEntry(1,3,3);
 A.changeEntry(2,1,4);
 A.changeEntry(2,2,5);
 A.changeEntry(2,3,6); 
 A.changeEntry(3,1,7);
 A.changeEntry(3,2,8);
 A.changeEntry(3,3,9);
 
	for(int i = 1; i < A.getSize()+1; i++){ 
         A.matrix[i].moveFront();
	 //while(A.matrix[i].index() != -1){
	 System.out.println(A.matrix[i]);
	 //A.matrix[i].moveNext();
	 //} 
 	}
 }
}
