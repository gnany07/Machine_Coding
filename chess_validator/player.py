class Address:
    def __init__(self, house_no, street, city, state, country, zipcode):
        self.HouseNo = house_no
        self.Street = street
        self.City = city
        self.State = state 
        self.Country = country
        self.ZipCode = zipcode
        return
    
class Person:
    def __init__(self, name, mobile, email, house_no, street, city, state, country, zipcode):
        self.Name = name
        self.Mobile = mobile
        self.Email = email
        self.Address = Address(house_no, street, city, state, country, zipcode)
        return

class User(Person):
    def __init__(self, name, mobile, email, house_no, street, city, state, country, zipcode, username, password):
        Person.__init__(self, name, mobile, email, house_no, street, city, state, country, zipcode)
        self.Username = username
        self.Password = password
        self.GameStats = []
        return

class Player:
    def __init__(self, color, game_id, username):
        self.Username = username
        self.Color = color 
        self.GameId = game_id
        self.Turn = False
        return