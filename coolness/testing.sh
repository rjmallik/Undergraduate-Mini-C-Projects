# zero arguments                                                                    
./coolness
# one argument                                                                      
./coolness 32
# two arguments                                                                     
./coolness 32.5 10

#additional arguments
./coolness 41

./coolness 11 8

./coolness 38 26


#out of range arguments
# temp out of range                                                                 
./coolness 55

# wind out of range                                                                 
./coolness 10 0

#temp above range
./coolness 65 8

#temp below range
./coolness -100 8

#temp above range wind out of range
./coolness 65 0

#temp below range wind out of range
./coolness -100 0
