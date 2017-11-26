class BookstoreController < ApplicationController
def welcome
@num_books=Book.count
end
def search
end
def result
@bookname = params[:title]
@bookz = Book.where(title:@bookname).all
@resString = "The Details of Book with title :"
if @bookz.count>0
@resString += " Is Given Below "
else
@resString += " not found in database !!!"
end
end
end
