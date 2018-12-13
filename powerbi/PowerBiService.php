<?php

/**
 * Power bi class.
 */
class PowerBiService {

  private $username;
  private $password;
  private $clientId;
  private $clientSecret;
  private $resource;
  private $groupId;

  /**
   * Constructor of the class.
   */
  public function __construct() {
    $this->username = variable_get('pbi_username', NULL);
    $this->password = variable_get('pbi_password', NULL);
    $this->clientId = variable_get('pbi_client_id', NULL);
    $this->clientSecret = variable_get('pbi_client_secret', null);
    $this->groupId = variable_get('pbi_group_id', NULL);
    $this->resource = 'https://analysis.windows.net/powerbi/api';
  }

  /**
   *
   */
  public function getAccessToken() {
    $fields = array(
      'grant_type' => 'password',
      'scope' => 'openid',
      'resource' => $this->resource,
      'client_id' => $this->clientId,
      'client_secret' => $this->clientSecret,
      'username' => $this->username,
      'password' => $this->password,
    );
    $options = array(
      // old url => "https://login.windows.net/common/oauth2/token",
      CURLOPT_URL => "https://login.microsoftonline.com/common/oauth2/token",
      CURLOPT_RETURNTRANSFER => TRUE,
      CURLOPT_ENCODING => "",
      CURLOPT_MAXREDIRS => 10,
      CURLOPT_TIMEOUT => 30,
      CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
      CURLOPT_CUSTOMREQUEST => "POST",
      CURLOPT_POSTFIELDS => $fields,
    );

    $curl = curl_init();
    curl_setopt_array($curl, $options);
    $tokenResponse = curl_exec($curl);
    $embedError = curl_error($curl);
    curl_close($curl);

    if ($embedError) {
      return $embedError;
    }
    else {
      $tokenResult = json_decode($tokenResponse, TRUE);
      $token = $tokenResult["access_token"];
      $embeddedToken = "Bearer " . ' ' . $token;
      setcookie("access_token", $token, $tokenResult['expires_on']);
      return $token;
    }
  }

  /**
   * Use the token to get an embedded URL using a GET request.
   */
  public function getembeddedURL($url, $method, $displyaType) {
    // Get token from cookie instead of making request each time until it expired.
    $access_token = (isset($_COOKIE["access_token"])) ? $_COOKIE["access_token"] : self::getAccessToken();
    $header = array(
      'Authorization:' . "Bearer $access_token",
      'Cache-Control: no-cache',
    );
    $options = array(
      CURLOPT_URL => $url . $this->groupId . '/' . $displyaType,
      CURLOPT_RETURNTRANSFER => TRUE,
      CURLOPT_ENCODING => "",
      CURLOPT_MAXREDIRS => 10,
      CURLOPT_TIMEOUT => 30,
      CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
      CURLOPT_CUSTOMREQUEST => $method,
      CURLOPT_HTTPHEADER => $header,
    );
    $curl = curl_init();
    curl_setopt_array($curl, $options);
    $embedResponse = curl_exec($curl);
    $embedResponse = json_decode($embedResponse, TRUE);
    $embedError = curl_error($curl);
    curl_close($curl);
    if ($embedError) {
      return $embedError;
    }
    else {
      return $embedResponse;
    }
  }

}
