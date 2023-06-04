# Anya 

[![Gitter](https://img.shields.io/gitter/room/DAVFoundation/DAV-Contributors.svg?style=flat-square)](https://matrix.to/#/!XPNMuvuskaGFEgmzjD:gitter.im?via=gitter.im)

A personal assistant for entrepreneurs, Anya helps entrepreneurs with their daily tasks.
She can manage enterprise resources, answer inquiries, or streamline employees' workloads.

In this repository, you will find the backend infrastructure that keeps her running.

It is built using the following tech stack:
* C++20
* Drogon Web Framework
* Postgresql
* glaze-json

## Setup and installation

### For Windows user:

Please setup [WSL](https://learn.microsoft.com/en-us/windows/wsl/install#prerequisites) if not done already done with the following details:
- use version 2
- use a debain based distro

Open the linux CLI and folow the [guide](#Guide).

### For Linux user:

Please check your linux distribution is based on debian if not then please lookup into setup/Makefile in the repository and find suitable packages for installation.

Further [guide](#Guide) is focused towards user having Debain.

### Guide:

Follow the below steps:

* **Step 1 : Clone**
    
    cd to your working directory and clone the repository.
    we will refer to working directory as \<work-dir>.

    ``` bash
    cd \<work-dir>;
    sudo apt-get install git -y;
    sudo apt-get update;
    git clone https://github.com/rishiagl/anya-cxx.git 
    ```

* **Step 2 : Install PostgresSQL**

    Install postgresSQL using the setup Makefile.

    ```bash
    cd anya-cxx/setup;
    sudo apt-get install make -y;
    sudo apt-get update;
    make postgres;
    ```

    now check the version of postgres installed

    ```bash
    psql -V
    ```

* **Step 3: Setup PostgresSQL**

    - Change password of the postgres user created during installation.(do not confuse this user with database user, this user is a OS user).

        ```bash
        sudo passwd postgres;
        ```
    - start the database server
        ```bash
        sudo service postgresql start;
        ```
    - run psql
        ```bash
        sudo -u postgres psql;
        ```
    - Now change the password of postgres user(Default database user created during installation)
        ```bash
        ALTER USER user_name WITH PASSWORD 'new_password';
        ```
    
    - Quit psql
        ```bash
        \q
        ```
    
    Now your postgresSQL is up and running with very very minimal configuration, for production use please read further blog on Securing your postgresSQL server.

-   **Step 4: Install Web Framework and Build System**\
    (Make Sure you are in setup directory)

    ```bash
    make install;
    ```

- **Step 5: Build and Run**
    (Assuming you are in setup directory)

    - Go to build directory
        ```bash
        cd ../build;
        ```

    - Run cmake
        ```bash
        sudo cmake ..
        ```

    - Run make
        ```bash
        sudo make
        ```

    - Run
        ```bash
        ./anya
        ```

## API Reference

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
| \<prefix> | GET | Get all Companies | None | JSON|
| \<prefix> | POST | Add single company | JSON | Plain Text | 
| \<prefix>/{pid} | GET | Get a single company | None | JSON |
| \<prefix>/{pid} | PUT | Update a single company | JSON | Plain Text |
| \<prefix>/{pid} | DELETE | Delete a single company | None | Plain Text |

Like-wise much more real-world entity's CRUD API has been implemented which will be documented in further iterations.