# Anya

Anya is a Business Management Tool that can any perform any function that a modern-day ERP(Enterprise Resource Planning) or CRM(Customer Resource Management) should perform.

She is built using the most elegant and fast tech stack:
* C++20
* Drogon Web Framework
* Postgresql
* glaze-json

## Current-Status: 

CRUD api's are available for the following resources:

### Company:

Relational Structure(Schema):

| Feature       | Data Type     | Constraint |
| ------------- | ------------- | ---------- |
| pid | integer  | auto generated |
| sid | string | auto generated |
| name | string | unrestricted text |
| address | string | unrestricted text |
| city | string | unrestricted text |
| state | string | unrestricted text |
| country | string | unrestricted text |
| cin | string | size == 21 |
| pan | string | size == 10 |
| gstin | string | size == 15 |

CRUD Api Endpoints:

prefix = http://<ip-address>:<port-number>/rest/api/company

| URI | HTTP Metthod | Use | Request Content type | Response Content type |
| --- | ------------ | --- | -------------------- | --------------------  |
| <prefix> | GET | Get all Companies | None | JSON|
| <prefix> | POST | Add single company | JSON | Plain Text | 
| <prefix>/{sid} | GET | Get a single company | None | JSON |
| <prefix>/{sid} | PUT | Update a single company | JSON | Plain Text |
| <prefix>/{sid} | DELETE | Delete a single company | None | Plain Text |
