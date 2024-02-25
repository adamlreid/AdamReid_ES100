# ES100
# Adam Reid
# Python code to lookup plate information

# Designed for use with auto_images directory

import time
import os
from selenium import webdriver
from selenium.webdriver.support.ui import Select
from selenium.webdriver.common.by import By

# Select web service
driver = webdriver.Chrome()

driver.get('https://www.lookupaplate.com/')

input_plate = driver.find_element(By.NAME, 'licensePlate')
input_plate.send_keys("126 ESW")

input_state = Select(driver.find_element(By.NAME, 'stateCode'))
input_state.select_by_value('LA')

time.sleep(2.1)

send_request1 = driver.find_element(By.CLASS_NAME, 'btn.btn-primary')
send_request1.click()

time.sleep(4.8)

driver.get('https://www.lookupaplate.com/')

send_request2 = driver.find_element(By.CLASS_NAME, 'btn.btn-neutral')
send_request2.click()

time.sleep(3.1)

send_request3 = driver.find_element(By.CLASS_NAME, 'btn.btn-link')
send_request3.click()

time.sleep(3.7)

file_input = driver.find_element(By.CSS_SELECTOR, "input[type='file']")
file_input.send_keys(os.getcwd()+'/auto_images/testLookup.jpg')

time.sleep(3.7)

driver.find_element(By.CLASS_NAME, 'btn.btn-primary.mx-auto.mt-3').click()

time.sleep(5)

driver.quit()
