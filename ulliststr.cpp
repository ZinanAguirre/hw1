#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val){
  /* It will first check if List is empty and after creating new item
      the value will be put in front of array*/ 
  if (tail_ == NULL) {
    Item* start = new Item;
    head_ = start;
    tail_ = start;
    head_->first = 0;
    head_->last = 1;
    head_->val[head_->first] = val;
    size_ = size_ + 1;
  }
  // It will check if item's array is not full and insert accordingly     
  else if (tail_->last < 10){
    tail_->last += 1;
    tail_->val[(tail_->last) - 1] = val;
    size_ += 1;
  }
  // Will create a new item towards back of list if the tail's array is full
  else{
    Item* final = new Item;
    tail_->next = final;
    final->next = NULL;
    final->prev = tail_;
    final->first = 0;
    final->last = 1;
    final->val[final->first] = val;
    tail_ = final;
    size_ = size_ + 1;
  }


}

void ULListStr::pop_back(){
    if(tail_== NULL){
      return;
    }
    /* Will check if there is more than one element in tail's array
      if so then it will remove the last value of array*/
    if (tail_->first < (tail_->last - 1)){
      tail_->val[(tail_->last) - 1] = "";
      tail_->last = (tail_->last) - 1;
      size_ = size_ - 1;
    }
    // If there is only one element then the tail and value must be deleted
    else{
      tail_->val[(tail_->last) - 1] = "";
      Item* temp = tail_;
      tail_ = tail_->prev;
      delete temp;
      if(tail_ != NULL){
        tail_->next = NULL;
      }
      else {
        head_ = NULL;
      }
      
      size_ = size_ - 1;
    }
}

void ULListStr::push_front(const std::string& val){
  /* It will first check if List is empty and after creating new item
      the value will be put in back of array*/ 
  if (head_ == NULL) {
    Item* start = new Item;
    head_ = start;
    tail_ = start;
    head_->first = 9;
    head_->last = 10;
    head_->val[head_->first] = val;
    size_ = size_ + 1;
  }
  // Will check if there is an array space in front of head's first array index value
  else if (head_->first > 0){
    head_->first = head_->first - 1;
    head_->val[head_->first] = val;
    size_ = size_ + 1;
  }
  /* Will create a new item and become the new head as 
     the new value will be added at the back of array */
  else{
    Item* start = new Item;
    head_->prev = start;
    start->next = head_;
    start->first = 9;
    start->last = 10;
    start->val[start->first] = val;
    head_ = start;
    size_ = size_ + 1;
  }

}

void ULListStr::pop_front(){
    if(head_ == NULL ){
      return;
    }
     /* Will check if there is more than one element in head's array
      if so then it will remove the last value of array*/
    else if(head_->first < (head_->last - 1)){
      head_->val[head_->first] = "";
      head_->first += 1;
      size_ = size_ - 1;
    }
    // If there is only one element then the head and only value must be deleted
    else{
      head_->val[head_->first] = "";
      Item* temp = head_;
      head_ = head_->next;
      delete temp;
      if(head_ != NULL){
        head_->prev = NULL;
      }
      else{
        tail_ = NULL;
      }
      size_ = size_ - 1;
    }
}

std::string const & ULListStr::back() const{
    return tail_->val[(tail_->last) - 1];
}

std::string const & ULListStr::front() const{
    return head_->val[head_->first];
}

/* This while loop will loop through the items in the list and 
     count each element of every array in every item until it matches the location
     index.
  */
std::string* ULListStr::getValAtLoc(size_t loc) const{
  size_t temp = 0;
  Item* now = head_; 
  while(now != NULL){
    for(size_t curr = now->first;  curr < now->last; curr++){
      if(temp == loc){
        return &now->val[curr];
      }
      temp += 1;
    }
    now = now->next;
  }
  return NULL;
}


void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
