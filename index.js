import express from 'express'

const app = new express();

app.use('/', express.static('public'))

app.listen(2000);