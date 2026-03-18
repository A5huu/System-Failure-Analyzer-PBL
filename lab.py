import numpy as np 
import pandas as pd

students={
    "roll_no":[1,2,3,4,5],
    "name":["Bishal","Jwsh","Manvendra","Rahul","Rakshit"],
    "sgpa":[0,9.0,7.7,8.6,7.8],
    "age":[19,17,18,20,0],
}
df=pd.DataFrame(students)
print("Original DataFrame:")
print(df)
df.loc[0,"sgpa"]=np.nan
df.loc[4,"age"]=np.nan
print("\nDataFrame after handling the missing values:")
dfhandled=df.dropna()
print(dfhandled)
df.loc[0,"sgpa"]=7.9
df.loc[4,"age"]=19
print("\nDataFrame after replacing NaN with Values:")
print(df)
