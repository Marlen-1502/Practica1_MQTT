
# include  < ESP8266WiFi.h >
# include  < PubSubClient.h >

// Actualícelos con valores adecuados para su red.

const  char * ssid = " Coronavirus (COVID-19) " ;
const  char * contraseña = "marlen*15*02" ;
const  char * mqtt_server = " 172.21.60.85 " ;
const  int buttonPin = 13 ;     // Pin del pulsador
const  int buttonPin2 = 14 ;     // Pin del pulsador
int d;
int i;

WiFiClient espClient;
Cliente PubSubClient (espClient);
long lastMsg = 0 ;
char msg [ 50 ];
valor int = 0 ;

void  setup_wifi () {

  retraso ( 10 );
  
  //  Conexion a red WiFi
  De serie. println ();
  De serie. print ( " Conectando a " );
  De serie. println (ssid);

  Wifi. comenzar (ssid, contraseña);

  while (WiFi. status ()! = WL_CONNECTED) {
    retraso ( 500 );
    De serie. print ( " . " );
  }

  randomSeed ( micros ());

  De serie. println ( " " );
  De serie. println ( " WiFi conectado " );
  De serie. println ( " Dirección IP: " );
  De serie. println (WiFi. localIP ());

}

 devolución de llamada nula ( char * topic, byte * payload, unsigned  int length) {
  De serie. print ( " Mensaje recibido [ " );
  De serie. imprimir (tema);
  De serie. print ( " ] " );
  para ( int i = 0 ; i <longitud; i ++) {
    De serie. print (( char ) carga útil [i]);
  }
  De serie. println ();

  // Encender LED al recibir un 1 como primer carácter
  if (( char ) payload [ 0 ] == ' 1 ' ) {
    digitalWrite (BUILTIN_LED, LOW);   
  }
  más {
    digitalWrite (BUILTIN_LED, HIGH);  // Apague el LED haciendo que el voltaje sea ALTO
  }

}

vacío  reconectar () {
  // Bucle hasta reconectar
  while (! cliente. conectado ()) {
    De serie. print ( " Intentando conexión MQTT ... " );
    // Crear una identificación de cliente aleatoria
    String clientId = " ESP8266Client- " ;
    clientId + = String ( aleatorio ( 0xffff ), HEX);
    // Intento de conectar
    if (client. connect (clientId. c_str ())) {
      De serie. println ( " conectado " );
      // Una vez conectado, publica un anuncio ...
      cliente. publicar ( " Naranja " , " Enviando mensaje... " );
      // ... y volver a suscribirte
       cliente. suscribirse ( " Naranja " );
    } más {
      De serie. print ( " falló, rc = " );
      De serie. print (cliente. estado ());
      De serie. println ( " intente nuevamente en 5 segundos " );
      // Espera 5 segundos antes de volver a intentar
      retraso ( 5000 );
    }
  }
}

 configuración nula () {
  
  pinMode (BUILTIN_LED, OUTPUT);     // Inicializa el pin BUILTIN_LED como salida
  De serie. comenzar ( 9600 );
  pinMode (buttonPin, INPUT_PULLUP);     
  pinMode (buttonPin2, INPUT_PULLUP);
  setup_wifi ();
  cliente. setServer (mqtt_server, 1883 );
  cliente. setCallback (devolución de llamada);
}

 bucle vacío () {
 largo ahora = millis ();

    ++ valor;
retraso ( 2000 );
    // Si el valor del pin del pulsador es ALTO es que esta pulsado
  if ( digitalRead (buttonPin) == HIGH) {    
           snprintf (msg, 50 , " POSICION DERECHA #% ld " , valor);
    
                          }
  sino  if ( digitalRead (buttonPin2) == HIGH) {
           snprintf (msg, 50 , " POSICION IZQUIERDA #% ld " , valor);
                                  }
 más {
        snprintf (msg, 50 , " POSICION CENTRAL #% ld " , valor);
  }
De serie. print ( " Publicar mensaje: " );
    De serie. println ( mensaje );
    cliente. publicar ( " Naranja " , msg);
  if (! cliente. conectado ()) {
    reconectar ();
  }
  cliente. bucle ();

 

  
}

void loop_post {
  if (WiFi. status () == WL_CONNECTED) {
    
    HTTPClient http;
    Cadena datos_a_enviar = " & disp = " + dispositivo;
    
    http. comenzar ( " " );
    
    
    int codigo_respuesta = htttp. POST (datos_a_enviar);
    
    if (codigo_respuesta> 0 ) {
      De serie. println ( " Codigo HTTP> " + Cadena (codigo_respuesta));
      
      if (cdigo_respuesta == 200 ) {
        Cadena cuerpo_respuest = http. getString ();
        De serie. println ( " El servidor responde" );
        De serie. println (cuerpo_respuesta);
  }
    } más {
       De serie. print ( " Error al enviar POST, codigo: " );
       De serie. println (codigo_respuesta);
    }
    
    http. fin ();
    
  } más {
    
    De serie. println ( " Error en la conexión WIFI " );
  }
 retraso ( 2000 );
}
  
}
