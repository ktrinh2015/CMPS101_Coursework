//----------------------------------------------------------------------------
//List.java
//
//ADT for List that contains the access and manipulation routines for List
//----------------------------------------------------------------------------
class List{
  private class Node{
	int data;
	Node next;
	Node prev;

	Node(int data) { this.data = data; next = null; prev = null;}

 }
 private Node front;
 private Node back;
 private int length;
 private int index;
 
 List(){
   front = back = null;
   length = 0;
   index = -1;
 }

 // Access Functions-----------------------------------------------------------------
  // length()
  // Returns length of this List.
 public int length(){
    return this.length;	
  }

 // index()
 // returns index of this List.
 public int index(){
     return this.index;
 }

 // front()
 // Returns front element.
 // Pre: length() >0, index() >=0
 public int front() {
    if(this.length() <= 0){
      throw new RuntimeException(
	"List Error: front() called on empty List");
    }
   
    return this.front.data;
 }
 
 // back()
 // Returns back element.
 // Pre: length() > 0, index() => 0
 public int back() {
    if(this.length() < 0){
      throw new RuntimeException(
	"List Error: back() called on empty List");
    }
    return this.back.data;
 }

 //get()
 //Returns cursor element.
 //Pre: length() > 0, index() >= 0
 public int get(){
 Node temp = this.front;
    if(this.length <= 0){
      return -1; 
    }
    if(this.index < 0){
       return -1;
    }
    for (int i = 0; i < this.index; i++){
        temp = temp.next;
    }
 return temp.data;
 }

 // equals(List L)
 // Returns true if and only if this List and L are the 
 // same integer sequence. The states of the cursors in the two Lists
 // are not used in determining equality.
 public boolean equals(List L){
     if(this.length == 0){
     return false;
     }
     if(L.length() == 0){
     return false;
     }
 Node temp = this.front;
 Node N = L.front;
    while(temp.next != null){
       if(temp.data != N.data){
          return false;  
       }
    temp = temp.next;
    N = N.next;
    } 
 return true;
 }

 // Manipulation Procedures---------------------------------------------------------
 //clear()
 //Resets this List to original empty state
 void clear(){
 this.front = null;
 this.back = null;
 this.length = 0;
 this.index = -1; 
 }

 //moveFront()
 //If List is non-empty, places cursor under the front element
 //Otherwise, does nothing
 public void moveFront(){
    if(this.length <= 0){
     throw new RuntimeException(
      "List Error: moveFront() called on empty List");
    }
  this.index = 0;
 }

 // moveBack()
 // If List is non-empty, places cursor under the back element
 // Otherwise, does nothing
 public void moveBack(){
    if(this.length < 0){
       throw new RuntimeException(
         "List Error: moveBack() called on empty List");
    }
 this.index = this.length - 1;
 }

 //movePrev()
 //If cursor is defined and is not at front,
 //moves cursor one step toward front of this List,
 //if cursor is defined and at front, cursor becomes undefined
 //if cursor is undefined, does nothing
 void movePrev(){
    if(this.length < 0){
       throw new RuntimeException(
	 "List Error: movePrev() called on undefined location"); 
    }
    if(this.length == 0){
       return;
    }
    this.index--;
 }

 // moveNext()
 // if cursor is defined and not at back,
 // moves cursor one step toward back of this List,
 // if cursor is defined and at back, cursor becomes
 // undefined, if cursor is undefined does nothing.
 public void moveNext(){
   if(this.length < 0){
      throw new RuntimeException(
        "List Error: moveNext() called on empty List");
   }
   if(this.index == this.length-1){
      this.index = -1;
      return;
   }
   if(this.index == -1){
      return;
   }
   this.index++;
 }

 // prepend(int data)
 // Insert new element into this List. If this List
 // is non-empty, insertion takes place before front element.
 public void prepend(int data){
 Node insert = new Node(data);
    if(this.length == 0){
      this.front = this.back = insert;
      this.length++; 
      return;
    }
    if(this.length == 1){
       this.front.prev = insert;
       insert.next = this.front;
       this.front = insert;
       this.length++;
       this.index++;
       return; 
    }
 this.front.prev = insert;
 insert.next = this.front;	 
 this.front = insert;
 this.length++;
 this.index++;
 }

 // append(int data)
 // Insert new element into this List.
 // If List is non-empty, insertion takes place
 // after back element.
 public void append(int data){
 Node insert = new Node(data); 
    if(this.length == 0){
       this.front = this.back = insert;
       this.length++;
       return; 
    }
    if(this.length == 1){
       this.front.next = insert;
       insert.prev = this.front;
       this.back = insert;     
       this.length++;
       return;
    }
 this.back.next = insert;
 insert.prev = this.back;
 this.back = insert;
 this.length++;
 }

 // insertBefore(int data)
 // Insert new element before cursor
 // Pre: length()>0, index>=0
 public void insertBefore(int data){
 Node temp = this.front;
 Node insert = new Node(data);
 Node prev = null;
     if(this.length <= 0){
	throw new RuntimeException(
	   "List Error: insertBefore() cannot insert into empty list");
     }
     if(this.index < 0){
	throw new RuntimeException(
	   "List Error: insertBefore() cannot insert into undefined location");
     }
     if(this.index == 0){
        this.front.prev = insert;
	insert.next = this.front;	
	insert.prev = null;
	this.front = insert;
     }
     else{
        for(int i = 0; i < this.index; i++){
           temp = temp.next;	
	}
     prev = temp.prev;
     temp.prev = insert;
     prev.next = insert;
     insert.prev = prev;
     insert.next = temp;	
     }
 this.length++;
 this.index++; 
 }

 // insertAfter(int data)
 // Insert new element after cursor
 // Pre: length() >0, index >= 0
 public void insertAfter(int data){
 Node temp = this.front;
 Node insert = new Node(data);
 Node next  = null;
     if(this.length <= 0){
	throw new RuntimeException(
	   "List Error: insertAfter() cannot insert into empty list");
     }
     if(this.index < 0){
	throw new RuntimeException(
	   "List Error: insertBefore() cannot insert into undefined location");
     }
     if(this.index == this.length-1){
        this.back.next = insert;
        insert.prev = this.back;
        insert.next = null;
        this.back = insert;   
     }
     else{
        for(int i = 0; i < this.index; i++){
           temp = temp.next;
	}
     next = temp.next;
     temp.next = insert;
     next.prev = insert;
     insert.prev = temp;
     insert.next = next;
     }
 this.length++;    
 }

 // deleteFront()
 // deletes the front element.
 // Pre: length() > 0
 public void deleteFront(){
    if(this.length <= 0){
       throw new RuntimeException(
          "List Error: Cannot deleteFront() cannot be called on empty List");
    }
    if(this.length() == 1){
    this.front = this.back = null;
    this.length = 0;
    this.index = -1;
    return;
    }
    if(this.length() == 2){
    this.front = this.front.next;
    this.front.next = null;
       if(this.index == 0){
       this.index = -1;
       }
       else{
       this.index--;
       }
    this.length--;
    return;
    }
 this.front = this.front.next;
 this.front.prev = null; 
    if(this.index == 0){
    this.index = -1;
    }
    else{
    this.index--;
    }
 this.length--;
 }
 
 // deleteBack()
 // Deletes the back element.
 // Pre: length()>0
 public void deleteBack(){
    if(this.length <= 0){
       throw new RuntimeException(
          "List Error: Cannot deleteBack() cannot be called on empty List");
    }
    if(this.length() == 1){
    this.front = this.back = null;
    this.length--;
    this.index = -1;
    return;
    }
    if(this.length() == 2){
    this.back = this.back.prev;
    this.front = this.back;
       if(this.index == this.length()-1){
       this.index = -1;
       }
    this.length--; 
    return;
    }
 this.back = this.back.prev;
 this.back.next = null;
    if(this.index == this.length()-1){
    this.index = -1;
    }
 this.length--;
 }
 
 // delete()
 // Delete cursor element, making cursor undefined.
 // Pre: length()>0, index() >=0
 public void delete(){
 Node temp = this.front;
 Node prev;
 Node next;
    if(this.length <= 0){
       throw new RuntimeException(
	 "List Error: delete() cannot be called on empty List");
    }
    if(this.index < 0){
       throw new RuntimeException(
	  "List Error: delete() cannot delete at undefined index");
    }
    if(this.index == 0){
          if(this.length == 1){
             this.front = this.back = null;
             this.length--;
             this.index = -1;
             return;
          }
          if(this.length() == 2){
             this.front = this.front.next;
             this.back = this.front;
             this.length--;
             this.index = -1;
             return;
          }
       this.front = this.front.next;
       this.front.prev = null;
       this.length--;
       this.index = -1;
       return; 
    } 
    if(this.index == this.length-1){  
       if(this.length == 2){       
          this.back = this.back.prev;
          this.front.next = null;
          this.length--;
          this.index = -1;
          return;
       }
       this.back = this.back.prev;
       this.back.next = null;
       this.length--;
       this.index = -1;
       return;
    } 
 
       for(int i = 0; i < index; i++){
	   temp = temp.next;
       }
    prev = temp.prev;
    next = temp.next;
    prev.next = next;
    next.prev = prev;
    
    this.index = -1;
    this.length--; 
    
 }

 // Other Functions ----------------------------------------------------
 
 // toString()
 // Overrides Object's toString() method. Returns a String
 // representation of this List consisting of a space
 // separated sequence of integers, with fornt on left.
 public String toString(){
    StringBuffer sb = new StringBuffer();
    Node N = this.front;
    while(N!=null){ 
       sb.append(N.data);
       sb.append(" ");
       N = N.next;
    }
    return new String(sb);
 }

 // copy()
 // Returns a new List representing the same integer sequence as this
 // List. The cursor in the new list is undefined, regardless of the
 // state of the cursor in this List. This List is unchanged.
 public List copy(){
 List L = new List();    
     if(this.length == 0){  
     return L; 
     } 
 Node temp = this.front;
    while(temp != null){
       L.append(temp.data); 
       temp = temp.next;   
    }
    L.length= this.length;
    L.index = -1;
    return L;
 }
}
