importación  paho . mqtt . cliente  como  mqtt
desde  pymongo  import  MongoClient
importar  pymongo
 tiempo de importación
 fecha y hora de importación


# La devolución de llamada para cuando el cliente recibe una respuesta CONNACK del servidor.
def  on_connect ( cliente , datos de usuario , banderas , rc ):
    print ( "Conectado con el código de resultado" + str ( rc ))

    # Suscribirse en on_connect () significa que si perdemos la conexión y
    # reconecte y luego se renovarán las suscripciones.
    cliente . suscribirse ( "Naranja" )

# La devolución de llamada para cuando se recibe un mensaje PUBLICAR del servidor.
def  ON_MESSAGE ( cliente , datos de usuario , msg ):
	print ( msg . topic + "" + str ( msg . payload ))
	#pymongo para la bd 
	myclient  =  pymongo . MongoClient ( "mongodb: // localhost: 27017 /" )
	mydb  =  myclient [ "mosco" ]
	mycol  =  mydb [ "mosquitto" ]
	#fecha = dateTimeObj.strftime ("% d-% b-% Y (% H:% M:% S.% f)")
	fecha  =  fecha y hora . fecha y hora ahora ()
	fecha_string  =  fecha . strftime ( '% Y-% m-% d' )
	tiempo_strin  =  fecha . strftime ( '% H:% M:% S.% f' )
	mydict  = {
		'estado' : msg . de carga útil . decodificar ( 'ascii' ),
		'date' : fecha_string ,
		'time' : tiempo_strin
	}
	imprimir ( mydict , "diccionario" )
	x  =  mycol . insert_one ( mydict )
	imprimir ( x , "respuesta" )

cliente  =  mqtt . Cliente ()
cliente . on_connect  =  on_connect
cliente . on_message  =  on_message

cliente . conectar ( "localhost" , 1883 , 60 )
    
#mongodb_db = 'foco'





# Bloqueo de llamadas que procesan el tráfico de red, despachan devoluciones de llamadas y
# maneja la reconexión.
# Hay otras funciones de bucle * () disponibles que proporcionan una interfaz roscada y un
# interfaz manual.
cliente . loop_forever ()