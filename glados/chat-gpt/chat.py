import openai

openai.api_key = "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"

model_engine = "text-davinci-003"

while True:
  prompt = input("Input: ")

  completion = openai.Completion.create(
   engine=model_engine,
   prompt=prompt,
   max_tokens=1024,
   n=1,
   stop=None,
   temperature=0.5,
  )

  print(completion['choices'][0]['text'])

'''
google-oauthlib-tool --scope https://www.googleapis.com/auth/assistant-sdk-prototype --scope https://www.googleapis.com/auth/gcm --save --headless --client-secrets client_secret_0.json
'''